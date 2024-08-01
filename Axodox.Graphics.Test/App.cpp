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

  struct Constants
  {
    XMFLOAT4X4 WorldViewProjection;
    float disFromEye;
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

    GraphicsPipelineStateDefinition simplePipelineStateDefinition{
      .RootSignature = &simpleRootSignature,
      .VertexShader = &simpleVertexShader,
      .PixelShader = &simplePixelShader,
      .RasterizerState = RasterizerFlags::CullClockwise,
      .DepthStencilState = DepthStencilMode::WriteDepth,
      .InputLayout = VertexPositionNormalTexture::Layout,
      .RenderTargetFormats = { Format::B8G8R8A8_UNorm },
      .DepthStencilFormat = Format::D32_Float
    };
    auto simplePipelineState = pipelineStateProvider.CreatePipelineStateAsync(simplePipelineStateDefinition).get();
        
    RootSignature<PostProcessingRootDescription> postProcessingRootSignature{ device };
    ComputeShader postProcessingComputeShader{ app_folder() / L"PostProcessingComputeShader.cso" };
    ComputePipelineStateDefinition postProcessingStateDefinition{
      .RootSignature = &postProcessingRootSignature,
      .ComputeShader = &postProcessingComputeShader
    };
    auto postProcessingPipelineState = pipelineStateProvider.CreatePipelineStateAsync(postProcessingStateDefinition).get();
        
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
    // Creation of meshlets
    auto heights = ImmutableTexture::readTextureData(app_folder() / L"47_473_19_062_15_100_100.png");
    std::vector<XMUINT2> vertices;
    ImmutableMesh mainmesh{ immutableAllocationContext, CreateWholeMap(heights, &vertices) };
    // Create Mesh at x,y coords
    ImmutableTexture texture{ immutableAllocationContext, app_folder() / L"47_473_19_062_15_100_100.png" };
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
    bool show_demo_window = true;
    bool show_another_window = false;
    DirectX::XMFLOAT4 clear_color = { 0.05f, 0.25f, 0.60f, 1.00f };
    #pragma endregion

    auto i = 0u;
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
        // L�t�sz�g
        auto projection = XMMatrixPerspectiveFovRH(90.f, float(resolution.x) / float(resolution.y), 0.01f, 10.f);
        // N�zett vektorok
        auto view = XMMatrixLookAtRH(XMVectorSet(1.5f * cos(i * 0.002f), 1.5f * sin(i * 0.002f), 1.5f, 1.f), XMVectorSet(0.f, 0.f, 0.f, 1.f), XMVectorSet(0.f, 0.f, 1.f, 1.f));
        auto world = XMMatrixIdentity();
        auto worldViewProjection = XMMatrixTranspose(world * view * projection);

        XMStoreFloat4x4(&constants.WorldViewProjection, worldViewProjection);
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
      // ImGui_ImplUwp_NewFrame();
      ImGui::NewFrame();
      // -----
      
      // ImGui Draws
      {
        if (show_demo_window)
          ImGui::ShowDemoWindow(&show_demo_window);

        {
          static float f = 0.0f;
          ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

          ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
          ImGui::Button("Test", { 200,20 });
          bool isHovered = ImGui::IsItemHovered();
          bool isFocused = ImGui::IsItemFocused();
          ImVec2 mousePositionAbsolute = ImGui::GetMousePos();
          ImVec2 screenPositionAbsolute = ImGui::GetItemRectMin();
          ImVec2 mousePositionRelative = ImVec2(mousePositionAbsolute.x - screenPositionAbsolute.x, mousePositionAbsolute.y - screenPositionAbsolute.y);

          ImGui::Text("Is mouse over screen? %s", isHovered ? "Yes" : "No");
          ImGui::Text("Is screen focused? %s", isFocused ? "Yes" : "No");
          ImGui::Text("Position: %f, %f", mousePositionRelative.x, mousePositionRelative.y);
          ImGui::Text("Mouse clicked: %s", ImGui::IsMouseDown(ImGuiMouseButton_Left) ? "Yes" : "No");

          ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
          ImGui::Checkbox("Another Window", &show_another_window);

          ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
          ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

          ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
          ImGui::End();
        }
      }
      
      // ImGui Rendering
      ImGui::Render();

      frames;
      // FrameContext* frameCtx = WaitForNextFrameResources();

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


      //Draw objects
      {
        auto mask = simpleRootSignature.Set(allocator, RootSignatureUsage::Graphics);
        mask.ConstantBuffer = resources.DynamicBuffer.AddBuffer(constants);
        mask.Texture = texture;

        allocator.SetRenderTargets({ renderTargetView }, resources.DepthBuffer.DepthStencil());
        simplePipelineState.Apply(allocator);
        mainmesh.Draw(allocator);

        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), allocator.operator->());
      }

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
      // ImGui_ImplUwp_Shutdown();
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
