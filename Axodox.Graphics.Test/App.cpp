#include "pch.h"
#include <Graphics/D3D12/Meshes/Primitives.cpp>
// #include <HeightmapReader.h>

// ImGUI
#include "imgui.h"
#include "imgui_impl_uwp.h"
#include <imgui_impl_dx12.h>

#include "Windows.h"

#include <winrt/Windows.Graphics.Display.h>
// -----

#include "Camera.h"

#define CBT_IMPLEMENTATION
#include "cbtlib/cbt.h"

#define LEB_IMPLEMENTATION
#include "leblib/leb.h"

using namespace std;
using namespace winrt;

using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::Graphics::Display;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;

using namespace Axodox::Graphics::D3D12;
using namespace Axodox::Infrastructure;
using namespace Axodox::Storage;
using namespace DirectX;

#pragma region CBT common

enum {
  BUFFER_CBT,
  BUFFER_CBT_DISPATCHER,
  BUFFER_LEB_DISPATCHER,
  BUFFER_TRIANGLE_COUNT,

  BUFFER_COUNT
};

enum {
  CLOCK_DISPATCHER,
  CLOCK_SUBDIVISION_SPLIT,
  CLOCK_SUBDIVISION_MERGE,
  CLOCK_SUM_REDUCTION,

  CLOCK_COUNT
};

MeshDescription basePlane;

ComputeShader* triprog = nullptr;
ComputeShader* target = nullptr;
ComputeShader* sumreductionPrepass = nullptr;
ComputeShader* sumreduction = nullptr;
ComputeShader* cbtDispatch = nullptr;
ComputeShader* LEBDispatch = nullptr;
ComputeShader* subdivision = nullptr;

struct LebRootSignature : public RootSignatureMask
{
  LebRootSignature(const RootSignatureContext& context) :
    RootSignatureMask(context)
  {
    Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
  }
};

#pragma endregion

#pragma region CBT Methods

bool LoadQueries()
{
  return true;
}

BufferRef CreateVertexBuffer(const ResourceAllocationContext& context, MeshDescription& description)
{
  return BufferRef(context.ResourceAllocator->CreateBuffer(BufferDefinition(description.Vertices)));
}

BufferRef CreateIndexBuffer(const ResourceAllocationContext& context, MeshDescription& description)
{
  return BufferRef(context.ResourceAllocator->CreateBuffer(BufferDefinition(description.Indices)));
}

bool LoadBuffers()
{
  return true;
}

bool LoadVertexIndexArray()
{
  VertexPositionNormalTexture* pVertex;
  basePlane.Vertices = BufferData(4, pVertex);

  auto size = 100.f;

  *pVertex++ = { {0.f, 0.f, 0.f}, { 0.f, 0.f, 1.f, 1.f }, {0.f,0.f} };
  *pVertex++ = { {size , 0.f, 0.f}, { 0.f, 0.f, 1.f, 1.f }, { 0.f,1.f } };
  *pVertex++ = { {0.f, size , 0.f}, { 0.f, 0.f, 1.f, 1.f }, { 1.f,0.f } };
  *pVertex++ = { {size , size , 0.f}, { 0.f, 0.f, 1.f, 1.f }, { 1.f,1.f } };

  uint32_t* pIndex;
  basePlane.Indices = BufferData(6, pIndex);

  *pIndex++ = 0; *pIndex++ = 1; *pIndex++ = 2;
  *pIndex++ = 2; *pIndex++ = 1; *pIndex++ = 3;

  basePlane.Topology = PrimitiveTopology::TriangleList;

  return true;
}

bool LoadPrograms()
{

  triprog = new ComputeShader(app_folder() / L"TriProg.cso");
  target = new ComputeShader(app_folder() / L"Target.cso");
  sumreductionPrepass = new ComputeShader(app_folder() / L"SumReductionPrepass.cso");
  sumreduction = new ComputeShader(app_folder() / L"SumReduction.cso");
  cbtDispatch = new ComputeShader(app_folder() / L"CBTDispatch.cso");
  LEBDispatch = new ComputeShader(app_folder() / L"LEBDispatch.cso");
  subdivision = new ComputeShader(app_folder() / L"Subdivision.cso");

  return true;
}

bool Load()
{
  bool success = true;

  success = success && LoadPrograms();
  success = success && LoadVertexIndexArray();
  success = success && LoadBuffers();
  success = success && LoadQueries();

  return success;
}

#define CBT_INIT_MAX_DEPTH 1
#define CBT_MAX_DEPTH 20
enum { MODE_TRIANGLE, MODE_SQUARE };
enum { BACKEND_CPU, BACKEND_GPU };
struct LongestEdgeBisection {
  cbt_Tree* cbt;
  struct {
    int mode;
    int backend;
    struct {
      float x, y;
    } target;
  } params;
  int32_t triangleCount;
} g_leb = {
    cbt_CreateAtDepth(CBT_MAX_DEPTH, CBT_INIT_MAX_DEPTH),
    {
        MODE_TRIANGLE,
        BACKEND_CPU,
        {0.49951f, 0.41204f}
    },
    0
};

float Wedge(const float* a, const float* b)
{
  return a[0] * b[1] - a[1] * b[0];
}


bool IsInside(const float faceVertices[][3])
{
  float target[2] = { g_leb.params.target.x, g_leb.params.target.y };
  float v1[2] = { faceVertices[0][0], faceVertices[1][0] };
  float v2[2] = { faceVertices[0][1], faceVertices[1][1] };
  float v3[2] = { faceVertices[0][2], faceVertices[1][2] };
  float x1[2] = { v2[0] - v1[0], v2[1] - v1[1] };
  float x2[2] = { v3[0] - v2[0], v3[1] - v2[1] };
  float x3[2] = { v1[0] - v3[0], v1[1] - v3[1] };
  float y1[2] = { target[0] - v1[0], target[1] - v1[1] };
  float y2[2] = { target[0] - v2[0], target[1] - v2[1] };
  float y3[2] = { target[0] - v3[0], target[1] - v3[1] };
  float w1 = Wedge(x1, y1);
  float w2 = Wedge(x2, y2);
  float w3 = Wedge(x3, y3);

  return (w1 >= 0.0f) && (w2 >= 0.0f) && (w3 >= 0.0f);
}

bool LoadCbtBuffer(CommandAllocator& resources)
{
  /*bool success = true;

  D3D12_CPU_DESCRIPTOR_HANDLE cbtBuffer;

  cbtBuffer.ByteWidth = 
  GLuint* buffer = &g_gl.buffers[BUFFER_CBT];

  if (glIsBuffer(*buffer))
    glDeleteBuffers(1, buffer);

  glGenBuffers(1, buffer);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);
  glBufferStorage(GL_SHADER_STORAGE_BUFFER,
    cbt_HeapByteSize(g_leb.cbt),
    cbt_GetHeap(g_leb.cbt),
    0);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BUFFER_CBT, *buffer);

  return glGetError() == GL_NO_ERROR;*/
  return true;
}

void UpdateSubdivisionCpuCallback_Split(
  cbt_Tree* cbt,
  const cbt_Node node,
  const void* userData
) {
  (void)userData;
  float faceVertices[][3] = {
      {0.0f, 0.0f, 1.0f},
      {1.0f, 0.0f, 0.0f}
  };

  if (g_leb.params.mode == MODE_TRIANGLE) {
    leb_DecodeNodeAttributeArray(node, 2, faceVertices);

    if (IsInside(faceVertices)) {
      leb_SplitNode(cbt, node);
    }
  }
  else {
    leb_DecodeNodeAttributeArray_Square(node, 2, faceVertices);

    if (IsInside(faceVertices)) {
      leb_SplitNode_Square(cbt, node);
    }
  }
}

void UpdateSubdivisionCpuCallback_Merge(
  cbt_Tree* cbt,
  const cbt_Node node,
  const void* userData
) {
  (void)userData;
  float baseFaceVertices[][3] = {
      {0.0f, 0.0f, 1.0f},
      {1.0f, 0.0f, 0.0f}
  };
  float topFaceVertices[][3] = {
      {0.0f, 0.0f, 1.0f},
      {1.0f, 0.0f, 0.0f}
  };

  if (g_leb.params.mode == MODE_TRIANGLE) {
    leb_DiamondParent diamondParent = leb_DecodeDiamondParent(node);

    leb_DecodeNodeAttributeArray(diamondParent.base, 2, baseFaceVertices);
    leb_DecodeNodeAttributeArray(diamondParent.top, 2, topFaceVertices);

    if (!IsInside(baseFaceVertices) && !IsInside(topFaceVertices)) {
      leb_MergeNode(cbt, node, diamondParent);
    }
  }
  else {
    leb_DiamondParent diamondParent = leb_DecodeDiamondParent_Square(node);

    leb_DecodeNodeAttributeArray_Square(diamondParent.base, 2, baseFaceVertices);
    leb_DecodeNodeAttributeArray_Square(diamondParent.top, 2, topFaceVertices);

    if (!IsInside(baseFaceVertices) && !IsInside(topFaceVertices)) {
      leb_MergeNode_Square(cbt, node, diamondParent);
    }
  }
}

void CPUUpdateSubdivision()
{
  static int pingPong = 0;

  if (g_leb.params.backend == BACKEND_CPU) {

    // djgc_start(g_gl.clocks[CLOCK_SUBDIVISION_SPLIT + pingPong]);
    if (pingPong == 0) {
      cbt_Update(g_leb.cbt, &UpdateSubdivisionCpuCallback_Split, NULL);
    }
    else {
      cbt_Update(g_leb.cbt, &UpdateSubdivisionCpuCallback_Merge, NULL);
    }
    // djgc_stop(g_gl.clocks[CLOCK_SUBDIVISION_SPLIT + pingPong]);

    //LoadCbtBuffer();
  }

  pingPong = 1 - pingPong;
}
#undef CBT_MAX_DEPTH

void DrawLeb(CommandAllocator& allocator, RootSignature<LebRootSignature> rootsignature)
{
  // prepare indirect draw command

  //glUseProgram(g_gl.programs[PROGRAM_LEB_DISPATCH]);
  //glDispatchCompute(1, 1, 1);
  //glMemoryBarrier(GL_ALL_BARRIER_BITS);

  //// draw
  //glEnable(GL_CULL_FACE);
  //glBindBuffer(GL_DRAW_INDIRECT_BUFFER, g_gl.buffers[BUFFER_LEB_DISPATCHER]);
  //glUseProgram(g_gl.programs[PROGRAM_TRIANGLES]);
  //glUniform2f(glGetUniformLocation(g_gl.programs[PROGRAM_TRIANGLES],
  //  "u_ScreenResolution"),
  //  g_window.width, g_window.height);
  //glBindVertexArray(g_gl.vertexarrays[VERTEXARRAY_EMPTY]);
  //glDrawArraysIndirect(GL_TRIANGLES, 0);
  //glBindVertexArray(0);
  //glUseProgram(0);
  //glDisable(GL_CULL_FACE);

  //RetrieveNodeCount();
}

#pragma endregion

#pragma region Loop Sections

struct FrameResources
{
  CommandAllocator Allocator;
  CommandFence Fence;
  CommandFenceMarker Marker;
  DynamicBufferManager DynamicBuffer;

  MutableTexture DepthBuffer;
  MutableTexture PostProcessingBuffer;
  descriptor_ptr<ShaderResourceView> ScreenResourceView;

  FrameResources(const ResourceAllocationContext& context) :
    Allocator(*context.Device),
    Fence(*context.Device),
    Marker(),
    DynamicBuffer(*context.Device),
    DepthBuffer(context),
    PostProcessingBuffer(context)
  { }
};

#pragma region Constants

struct Constants
{
  XMFLOAT4X4 WorldViewProjection;
  XMUINT2 MeshletSize;
  float disFromEye;
  XMUINT2 lineDraw;
};

#pragma endregion

#pragma region RootSignatures

struct SimpleRootDescription : public RootSignatureMask
{
  RootDescriptor<RootDescriptorType::ConstantBuffer> ConstantBuffer;
  RootDescriptorTable<1> Texture;
  StaticSampler Sampler;

  SimpleRootDescription(const RootSignatureContext& context) :
    RootSignatureMask(context),
    ConstantBuffer(this, { 0 }, ShaderVisibility::Vertex),
    Texture(this, { DescriptorRangeType::ShaderResource }, ShaderVisibility::Pixel),
    Sampler(this, { 0 }, Filter::Linear, TextureAddressMode::Clamp, ShaderVisibility::Pixel)
  {
    Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
  }
};

#pragma endregion


void DrawImmutableMesh(
  CommandAllocator& allocator,
  RootSignature<SimpleRootDescription> rootsignature,
  FrameResources& resources,
  Constants constants,
  ImmutableTexture* texture,
  ImmutableMesh* mainmesh,
  const RenderTargetView* renderTargetView,
  PipelineState& simplePipelineState)
{
  auto mask = rootsignature.Set(allocator, RootSignatureUsage::Graphics);
  mask.ConstantBuffer = resources.DynamicBuffer.AddBuffer(constants);
  mask.Texture = *texture;

  allocator.SetRenderTargets({ renderTargetView }, resources.DepthBuffer.DepthStencil());
  simplePipelineState.Apply(allocator);
  mainmesh->Draw(allocator);
}

#pragma endregion


struct App : implements<App, IFrameworkViewSource, IFrameworkView>
{
  IFrameworkView CreateView()
  {
    return *this;
  }

  void Initialize(CoreApplicationView const&)
  {
  }

  void Load(hstring const&)
  {
  }

  void Uninitialize()
  {
  }

  struct PostProcessingRootDescription : public RootSignatureMask
  {
    RootDescriptor<RootDescriptorType::ConstantBuffer> ConstantBuffer;
    RootDescriptorTable<1> InputTexture;
    RootDescriptorTable<1> OutputTexture;
    StaticSampler Sampler;

    PostProcessingRootDescription(const RootSignatureContext& context) :
      RootSignatureMask(context),
      ConstantBuffer(this, { 0 }),
      InputTexture(this, { DescriptorRangeType::ShaderResource }),
      OutputTexture(this, { DescriptorRangeType::UnorderedAccess }),
      Sampler(this, { 0 }, Filter::Linear, TextureAddressMode::Clamp)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };

  struct CBTRootDescriptor : public RootSignatureMask
  {
    CBTRootDescriptor(const RootSignatureContext& context) :
      RootSignatureMask(context)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };

  #pragma region ImGui constants
  static int const NUM_BACK_BUFFERS = 3;
  static const int NUM_FRAMES_IN_FLIGHT = 3;
  bool m_windowClosed = false;
  com_ptr<ID3D12DescriptorHeap> m_pd3dRtvDescHeap;
  com_ptr<ID3D12DescriptorHeap> m_pd3dSrvDescHeap;
  #pragma endregion

  void Run()
  {
    CoreWindow window = CoreWindow::GetForCurrentThread();
    CoreDispatcher dispatcher = window.Dispatcher();
    window.Activate();

    #pragma region Setup
    GraphicsDevice device{};
    CommandQueue directQueue{ device };
    CoreSwapChain swapChain{ directQueue, window, SwapChainFlags::IsShaderResource };

    PipelineStateProvider pipelineStateProvider{ device };

    RootSignature<SimpleRootDescription> simpleRootSignature{ device };
    VertexShader simpleVertexShader{ app_folder() / L"SimpleVertexShader.cso" };
    PixelShader simplePixelShader{ app_folder() / L"SimplePixelShader.cso" };
    // HullShader simpleHullShader{ app_folder() / L"SimpleHullShader.cso"};

    GraphicsPipelineStateDefinition simplePipelineStateDefinition{
      .RootSignature = &simpleRootSignature,
      .VertexShader = &simpleVertexShader,
      //.HullShader = &simpleHullShader,
      .PixelShader = &simplePixelShader,
      .RasterizerState = RasterizerFlags::CullClockwise,
      .DepthStencilState = DepthStencilMode::WriteDepth,
      .InputLayout = VertexPositionNormalTexture::Layout,
      //.TopologyType = PrimitiveTopologyType::Patch,
      .RenderTargetFormats = { Format::B8G8R8A8_UNorm },
      .DepthStencilFormat = Format::D32_Float,
    };
    auto simplePipelineState = pipelineStateProvider.CreatePipelineStateAsync(simplePipelineStateDefinition).get();
        
    RootSignature<PostProcessingRootDescription> postProcessingRootSignature{ device };
    ComputeShader postProcessingComputeShader{ app_folder() / L"PostProcessingComputeShader.cso" };
    ComputePipelineStateDefinition postProcessingStateDefinition{
      .RootSignature = &postProcessingRootSignature,
      .ComputeShader = &postProcessingComputeShader
    };

    RootSignature<CBTRootDescriptor> CBTRootSignature{ device };
    ComputeShader CbtCS{ app_folder() / L"CbtCommon.cso" };
    ComputePipelineStateDefinition CbtStateDef{
      .RootSignature = &CBTRootSignature,
      .ComputeShader = &CbtCS
    };

    auto postProcessingPipelineState = pipelineStateProvider.CreatePipelineStateAsync(postProcessingStateDefinition).get();
    auto CBTPipelineState = pipelineStateProvider.CreatePipelineStateAsync(CbtStateDef).get();

    GroupedResourceAllocator groupedResourceAllocator{ device };
    ResourceUploader resourceUploader{ device };
    CommonDescriptorHeap commonDescriptorHeap{ device, 2 };
    DepthStencilDescriptorHeap depthStencilDescriptorHeap{ device };
    ResourceAllocationContext immutableAllocationContext{
      .Device = &device,
      .ResourceAllocator = &groupedResourceAllocator,
      .ResourceUploader = &resourceUploader,
      .CommonDescriptorHeap = &commonDescriptorHeap,
      .DepthStencilDescriptorHeap = &depthStencilDescriptorHeap
    };

    // Read height data
    // TODO: break down map to meshlets and distribute them in compact buffers
    //std::filesystem::path fPath =
      //app_folder() / L"47_473_19_062_15_100_100.png";
      //app_folder() / L"27_985_86_924_10_250_250.png";
      //app_folder() / L"27_985_86_924_10_500_250.png";
      //app_folder() / L"27_985_86_924_10_500_500.png";
      //app_folder() / L"27_985_86_924_10_1000_500.png";
      //app_folder() / L"27_985_86_924_10_1000_1000.png";
      //app_folder() / L"27_985_86_924_10_2000_1000.png";
      //app_folder() / L"27_985_86_924_10_2000_2000.png"; // LIMIT
      //app_folder() / L"27_985_86_924_10_4000_4000.png"; // ERROR
    // Creation of meshlets
    //auto heights = ImmutableTexture::readTextureData(fPath);
    // Width, Height
    // XMVECTOR MeshletSize{ heights.at(0).size(), heights.size()};
    //std::vector<XMUINT2> vertices;
    // Create Mesh at x,y coords

    LoadVertexIndexArray();

    ImmutableMesh mainmesh{ immutableAllocationContext, basePlane };
    ImmutableTexture texture{ immutableAllocationContext, app_folder() / L"image.jpeg" };
    
    
    // TODO: Stuck 2k heightmaps at
    // AllocateResources(_resources);
    groupedResourceAllocator.Build();

    auto mutableAllocationContext = immutableAllocationContext;
    CommittedResourceAllocator committedResourceAllocator{ device };
    mutableAllocationContext.ResourceAllocator = &committedResourceAllocator;

    array<FrameResources, 2> frames{ mutableAllocationContext, mutableAllocationContext };

    swapChain.Resizing(no_revoke, [&](SwapChain*) {
      for (auto& frame : frames) frame.ScreenResourceView.reset();
      commonDescriptorHeap.Clean();
      });

    #pragma endregion
    
    #pragma region ImGui Setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // High DPI scaling
    DisplayInformation currentDisplayInformation = DisplayInformation::GetForCurrentView();
    float dpi = currentDisplayInformation.LogicalDpi() / 96.0f;
    io.DisplayFramebufferScale = { dpi, dpi };                // TODO: Handle DPI change

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplUwp_InitForCurrentView();
    //ImGui::StyleColorsLight();
    {
      D3D12_DESCRIPTOR_HEAP_DESC desc = {};
      desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
      desc.NumDescriptors = NUM_BACK_BUFFERS;
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
      desc.NodeMask = 1;
      winrt::check_hresult(device.get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dRtvDescHeap)));
    }

    {
      D3D12_DESCRIPTOR_HEAP_DESC desc = {};
      desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
      desc.NumDescriptors = 1;
      desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
      winrt::check_hresult(device.get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dSrvDescHeap)));
    }
    // Setup Platform/Renderer backends
    // com_ptr<ID3D12DescriptorHeap> m_pd3dSrvDescHeap;
    ImGui_ImplDX12_Init(device.get(), NUM_FRAMES_IN_FLIGHT,
      DXGI_FORMAT_R8G8B8A8_UNORM, m_pd3dSrvDescHeap.get(),
      m_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
      m_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

    // Our state
    DirectX::XMFLOAT4 clear_color = { 0.05f, 0.25f, 0.60f, 1.00f };
    #pragma endregion

    // Camera setup
    bool firstperson = false;
    bool& quit = m_windowClosed;
    Camera cam;

    // Event setup
    {
      window.KeyDown([&cam, &quit, &firstperson](CoreWindow const&,
        KeyEventArgs const& args) {
          if (ImGui::GetIO().WantCaptureKeyboard)
            return;
          switch (args.VirtualKey()) {
          case Windows::System::VirtualKey::Escape:
            quit = true;
            break;
          /*case Windows::System::VirtualKey::Space:
            firstperson = !firstperson;
            cam.SetFirstPerson(firstperson);
            break;*/

          default:
            cam.KeyBoardDown(args);
            break;
          }
        });
      window.KeyUp([&cam](CoreWindow const&, KeyEventArgs const& args) {
        if (ImGui::GetIO().WantCaptureKeyboard)
          return;
        cam.KeyboardUp(args);
        });
      window.PointerMoved([&cam](CoreWindow const&, PointerEventArgs const& args) {
        if (ImGui::GetIO().WantCaptureMouse)
          return;
        cam.MouseMove(args);
        });
      window.PointerWheelChanged(
        [&cam](CoreWindow const&, PointerEventArgs const& args) {
          if (ImGui::GetIO().WantCaptureMouse)
            return;
          cam.MouseWheel(args);
        });
    }

#pragma region CBT INIT



#pragma endregion

    auto i = 0u;
    bool LineMode = false;
    while (!m_windowClosed)
    {
      //Process user input
      dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

      //Get frame resources
      auto& resources = frames[i++ & 0x1u];
      auto renderTargetView = swapChain.RenderTargetView();

      //Wait until buffers can be reused
      if (resources.Marker) resources.Fence.Await(resources.Marker);

      //Update constants
      Constants constants{};
      auto resolution = swapChain.Resolution();
      {
        // ImGUI
        io.DisplaySize = ImVec2(resolution.x, resolution.y);
        // -----
        // Camera
        cam.SetAspect(float(resolution.x) / float(resolution.y));
        cam.Update(io.DeltaTime);
        // Látószög
        auto projection = XMMatrixPerspectiveFovRH(90.f, float(resolution.x) / float(resolution.y), 0.01f, 1000.f);
        // Nézett vektorok
        auto view =//  cam.GetViewMatrix();
          XMMatrixLookAtRH(
            cam.GetEye(),
            cam.GetAt(),
            cam.GetWorldUp());
        auto world = XMMatrixIdentity();
        auto worldViewProjection = XMMatrixTranspose(world * view * projection);

        XMMATRIX model = XMMatrixTranslation(-100.f / 2.0f, 20.0f, +100.f / 2.0f);

        /*for (int i = 0; i < 3; ++i)
          for (int j = 0; j < 2; ++j) 
          {
            cam.frustum[i * 2 + j].x = mvp[0][3] + (j == 0 ? mvp[0][i] : -mvp[0][i]);
            cam.frustum[i * 2 + j].y = mvp[1][3] + (j == 0 ? mvp[1][i] : -mvp[1][i]);
            cam.frustum[i * 2 + j].z = mvp[2][3] + (j == 0 ? mvp[2][i] : -mvp[2][i]);
            cam.frustum[i * 2 + j].w = mvp[3][3] + (j == 0 ? mvp[3][i] : -mvp[3][i]);
            XMFLOAT4 tmp = cam.frustum[i * 2 + j];
            cam.frustum[i * 2 + j] *= XMVector3Normalize(XMVECTOR(tmp.x, tmp.y, tmp.z));
          }*/

        XMStoreFloat4x4(&constants.WorldViewProjection, worldViewProjection);
        //XMStoreUInt2(&constants.MeshletSize,MeshletSize);
        XMStoreFloat(&constants.disFromEye,XMVECTOR{0.33f});
      }

      //Ensure depth buffer
      if (!resources.DepthBuffer || !TextureDefinition::AreSizeCompatible(*resources.DepthBuffer.Definition(), renderTargetView->Definition()))
      {
        auto depthDefinition = renderTargetView->Definition().MakeSizeCompatible(Format::D32_Float, TextureFlags::DepthStencil);
        resources.DepthBuffer.Allocate(depthDefinition);
      }

      //Ensure screen shader resource view
      if (!resources.ScreenResourceView || resources.ScreenResourceView->Resource() != renderTargetView->Resource())
      {
        Texture screenTexture{ renderTargetView->Resource() };
        resources.ScreenResourceView = commonDescriptorHeap.CreateShaderResourceView(&screenTexture);
      }

      //Ensure post processing buffer
      if (!resources.PostProcessingBuffer || !TextureDefinition::AreSizeCompatible(*resources.PostProcessingBuffer.Definition(), renderTargetView->Definition()))
      {
        auto postProcessingDefinition = renderTargetView->Definition().MakeSizeCompatible(Format::B8G8R8A8_UNorm, TextureFlags::UnorderedAccess);
        resources.PostProcessingBuffer.Allocate(postProcessingDefinition);
      }


      // ImGui
      ImGui_ImplDX12_NewFrame();
      ImGui_ImplUwp_NewFrame();
      ImGui::NewFrame();
      // -----

      // ImGui Draws
      {
        {
          ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
          ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
          if (ImGui::Button("Reset Camera", { 200,20 }))
          {
            cam = Camera();
          }
          if (ImGui::Checkbox("Line view", &LineMode)) {
            simplePipelineStateDefinition = {
              .RootSignature = &simpleRootSignature,
              .VertexShader = &simpleVertexShader,
              //.HullShader = &simpleHullShader,
              .PixelShader = &simplePixelShader,
              .RasterizerState = LineMode ? RasterizerFlags::Wireframe : RasterizerFlags::CullClockwise,
              .DepthStencilState = DepthStencilMode::WriteDepth,
              .InputLayout = VertexPositionNormalTexture::Layout,
              //.TopologyType = PrimitiveTopologyType::Patch,
              .RenderTargetFormats = { Format::B8G8R8A8_UNorm },
              .DepthStencilFormat = Format::D32_Float,
            };
            simplePipelineState = pipelineStateProvider.CreatePipelineStateAsync(simplePipelineStateDefinition).get();
          }
          bool isHovered = ImGui::IsItemHovered();
          bool isFocused = ImGui::IsItemFocused();
          ImVec2 mousePositionAbsolute = ImGui::GetMousePos();
          ImVec2 screenPositionAbsolute = ImGui::GetItemRectMin();
          ImVec2 mousePositionRelative = ImVec2(mousePositionAbsolute.x - screenPositionAbsolute.x, mousePositionAbsolute.y - screenPositionAbsolute.y);

          ImGui::Text("Is mouse over screen? %s", isHovered ? "Yes" : "No");
          ImGui::Text("Is screen focused? %s", isFocused ? "Yes" : "No");
          ImGui::Text("Position: %f, %f", mousePositionRelative.x, mousePositionRelative.y);
          ImGui::Text("Mouse clicked: %s", ImGui::IsMouseDown(ImGuiMouseButton_Left) ? "Yes" : "No");

          ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

          ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
          ImGui::End();
        }
      }

      // ImGui Rendering
      ImGui::Render();

      //Begin frame command list
      auto& allocator = resources.Allocator;
      {
        allocator.Reset();
        allocator.BeginList();
        allocator.TransitionResource(*renderTargetView, ResourceStates::Present, ResourceStates::RenderTarget);

        committedResourceAllocator.Build();
        depthStencilDescriptorHeap.Build();

        commonDescriptorHeap.Build();
        commonDescriptorHeap.Set(allocator);

        renderTargetView->Clear(allocator, clear_color);
        resources.DepthBuffer.DepthStencil()->Clear(allocator);
      }

      //CBT
      {
        allocator.TransitionResource(*renderTargetView, ResourceStates::RenderTarget, ResourceStates::NonPixelShaderResource);

        auto mask = CBTRootSignature.Set(allocator, RootSignatureUsage::Compute);
        CBTPipelineState.Apply(allocator);

        // auto definition = resources.PostProcessingBuffer.Definition();
        allocator.Dispatch(1, 1);
      }

      //Draw objects
      {
        DrawImmutableMesh(
          allocator, simpleRootSignature,
          resources, constants, &texture,
          &mainmesh, renderTargetView, simplePipelineState);
      }

      ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), allocator.operator->());

      //Post processing
      {
        allocator.TransitionResource(*renderTargetView, ResourceStates::RenderTarget, ResourceStates::NonPixelShaderResource);

        auto mask = postProcessingRootSignature.Set(allocator, RootSignatureUsage::Compute);
        mask.ConstantBuffer = resources.DynamicBuffer.AddBuffer(i * 0.02f);
        mask.InputTexture = *resources.ScreenResourceView;
        mask.OutputTexture = *resources.PostProcessingBuffer.UnorderedAccess();
        postProcessingPipelineState.Apply(allocator);

        auto definition = resources.PostProcessingBuffer.Definition();
        allocator.Dispatch(definition->Width / 16 + 1, definition->Height / 16 + 1);

        allocator.TransitionResources({
          { resources.PostProcessingBuffer, ResourceStates::UnorderedAccess, ResourceStates::CopySource },
          { *renderTargetView, ResourceStates::NonPixelShaderResource, ResourceStates::CopyDest }
        });

        allocator.CopyResource(resources.PostProcessingBuffer, *renderTargetView);

        allocator.TransitionResources({
          { resources.PostProcessingBuffer, ResourceStates::CopySource, ResourceStates::UnorderedAccess },
          { *renderTargetView, ResourceStates::CopyDest, ResourceStates::RenderTarget }
        });
      }

      //End frame command list
      {
        allocator.TransitionResource(*renderTargetView, ResourceStates::RenderTarget, ResourceStates::Present);
        auto drawCommandList = allocator.EndList();

        allocator.BeginList();
        resources.DynamicBuffer.UploadResources(allocator);
        resourceUploader.UploadResourcesAsync(allocator);
        auto initCommandList = allocator.EndList();

        directQueue.Execute(initCommandList);
        directQueue.Execute(drawCommandList);
        resources.Marker = resources.Fence.EnqueueSignal(directQueue);
      }

      //Present frame
      swapChain.Present();
    }

    // ImGui Cleanup
    {
      ImGui_ImplDX12_Shutdown();
      ImGui_ImplUwp_Shutdown();
      ImGui::DestroyContext();
    }
  }

  void SetWindow(CoreWindow const& /*window*/)
  {

  }

  #pragma region Events
  #pragma endregion

};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
  CoreApplication::Run(make<App>());
}
