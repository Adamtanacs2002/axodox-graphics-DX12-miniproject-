#include <pch.h>
#include <App.h>

// ImGUI
#include "cbt_helper.h"
#include "../ImGUI/Includes/includes.h"

#include "Windows.h"

#include <winrt/Windows.Graphics.Display.h>
// -----

#include "Camera.h"

#include <WrapperAddons/BufferWithView.h>

#include "BisectorMesh.h"

using namespace DrawPrimitivesUtil;

void App::ImGuiCommands(
Camera& cam,
GraphicsPipelineStateDefinition& simplePipelineStateDefinition,
GraphicsPipelineStateDefinition& wireFrameStateDefinition,
PipelineState& simplePipelineState,
PipelineStateProvider pipelineStateProvider)
{
    // ImGui Draws
    
    ImVec2 mousePositionAbsolute = ImGui::GetMousePos();

    idList = cbt.PopulateListCbt();

    triList = PopulateList(idList, BaseTri,{255,255,255});

    if (ImGui::Begin("Concurrent Binary Tree Demo"))
    {
        ImGui::Text("Depth : ");
        ImGui::SameLine();
        ImGui::TextColored(ImColor{ 250,250,50 }, 
            std::to_string((cbt.depth)).c_str());

    	ImGui::Text("Bitfield values: ");
        ImGui::SameLine();
        ImGui::TextColored(ImColor{ 250,250,50 },
            cbt.DisplayBinField().c_str());

        ImGui::Text("Decoded :");
        for (auto tmp : idList)
        {
            ImGui::SameLine();
            if (tmp == focusedTriId)
				ImGui::TextColored(ImColor{ 255,150,50 }, std::to_string(tmp).c_str());
            else
                ImGui::Text(std::to_string(tmp).c_str());
        }
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2{ 300,300 });
    ImGui::SetNextWindowPos({60,150});

	if (ImGui::Begin("LEB Demo Window"))
    {
		ImDrawList* drawlist = ImGui::GetWindowDrawList();
		ImVec2 wpos = ImGui::GetWindowPos();
        ImVec2 mousePositionRelative = { mousePositionAbsolute.x - wpos.x, mousePositionAbsolute.y - wpos.y };

        if (ImGui::Button("Reset Triangle"))
        {
            cbt.Reset();
        }


        focusedTriId = -1;
        for (int i = 0; i < triList.size(); i++)
        {
            auto tri = triList.at(i);

            if (PointInTriangle(mousePositionRelative, tri))
            {
                ImColor vtCols[3] = {
                        ImColor{255,100,100},
                        ImColor{100,255,100},
                        ImColor{120,120,255}
                };

                drawlist->AddCircleFilled(
                    *tri.p0 + wpos, 5.0f, vtCols[0]);
                drawlist->AddCircleFilled(
                    *tri.p1 + wpos, 5.0f, vtCols[1]);
                drawlist->AddCircleFilled(
                    *tri.p2 + wpos, 5.0f, vtCols[2]);
            }

            if (std::find(highlightID.begin(), highlightID.end(), tri.id) != highlightID.end())
            {
            	if (tri.id == highlightID[2])
                {
                    drawlist->AddTriangleFilled(
                        *tri.p0 + wpos,
                        *tri.p1 + wpos,
                        *tri.p2 + wpos, ImColor{ 0,255,100,255 });
                }
                else
                {
                    drawlist->AddTriangleFilled(
                        *tri.p0 + wpos,
                        *tri.p1 + wpos,
                        *tri.p2 + wpos, tri.col);
                }
            }

            if (PointInTriangle(mousePositionRelative, tri))
            {
                focusedTriId = tri.id;
                {
                    ImColor color = tri.id == highlightID[3] ?
                        ImColor{ 255,150,150 } : tri.col;
                    drawlist->AddTriangleFilled(
                        *tri.p0 + wpos,
                        *tri.p1 + wpos,
                        *tri.p2 + wpos, color);
                }
            }
            else
            {
                drawlist->AddTriangle(
                    *tri.p0 + wpos,
                    *tri.p1 + wpos,
                    *tri.p2 + wpos, tri.col);
            }
        }
    }
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2{ 400,200 });
    ImGui::SetNextWindowPos({ 60,475 });

	if (ImGui::Begin("Triangle Data"))
    {
        if (ImGui::BeginListBox("Triangles"))
        {
            for (auto tri : triList)
            {
                if (ImGui::TreeNode(
                    ("Triangle" + std::to_string(tri.id) + " data").c_str()))
                {

                    ImGui::Text("Vertex Positions");
                    ImGui::Text("%d (%f,%f)", 0, tri.p0->x, tri.p0->y);
                    ImGui::Text("%d (%f,%f)", 1, tri.p1->x, tri.p1->y);
                	ImGui::Text("%d (%f,%f)", 2, tri.p2->x, tri.p2->y);

                    ImGui::Text("Vertex Indices: %d %d %d", 0, 1, 2);

                    std::array<int,4> otherTris= GetNeighbours(tri.id);

                    ImGui::Text("Neighbours : %d %d %d",
                        otherTris[0], otherTris[1], otherTris[2]);

                    ImGui::TreePop();
                }
            }
        }

        ImGui::EndListBox();
    }

    ImGui::End();

    triList.clear();
    idList.clear();
}

App::App() :
window(nullptr),
dispatcher(nullptr)
{
	directQueue = make_shared<CommandQueue>(CommandQueue{ device });
}

void App::InitWindow()
{
    window = CoreWindow::GetForCurrentThread();
    dispatcher = window.Dispatcher();
    window.Activate();
}

void App::Run()
{
    InitWindow();

#pragma region Setup
    // Get graphics device in header
    auto swapChain = CoreSwapChain{ *directQueue.get(), window, SwapChainFlags::IsShaderResource };

    // Setup Core SwapChain for display frames

    // Setup Required pipelines
    PipelineStateProvider pipelineStateProvider = PipelineStateProvider{ device };

    RootSignature<SimpleRootDescription> simpleRootSignature{ device };
    VertexShader simpleVertexShader{ app_folder() / L"SimpleVertexShader.cso" };
    PixelShader simplePixelShader{ app_folder() / L"SimplePixelShader.cso" };
    HullShader simpleHullShader{ app_folder() / L"SimpleHullShader.cso" };
    DomainShader simpleDomainShader{ app_folder() / L"SimpleDomainShader.cso" };
    GeometryShader simpleGeometryShader{ app_folder() / L"SimpleGeometryShader.cso" };


    GraphicsPipelineStateDefinition simplePipelineStateDefinition{
      .RootSignature = &simpleRootSignature,
      .VertexShader = &simpleVertexShader,
      .DomainShader = &simpleDomainShader,
      .HullShader = &simpleHullShader,
      .GeometryShader = &simpleGeometryShader,
      .PixelShader = &simplePixelShader,
      .RasterizerState = RasterizerFlags::CullClockwise,
      .DepthStencilState = DepthStencilMode::WriteDepth,
      .InputLayout = VertexPositionTexture::Layout,
      .TopologyType = PrimitiveTopologyType::Patch,
      .RenderTargetFormats = { Format::B8G8R8A8_UNorm },
      .DepthStencilFormat = Format::D32_Float,
    };

    GraphicsPipelineStateDefinition wireFrameStateDefinition(simplePipelineStateDefinition);
    wireFrameStateDefinition.RasterizerState = { RasterizerFlags::Wireframe };

    auto simplePipelineState = pipelineStateProvider.CreatePipelineStateAsync(simplePipelineStateDefinition).get();

    RootSignature<ConcurrentBinaryTreeRootDesc> DispatcherKernelSignature{ device };
    ComputeShader DispatcherKernelCS{ app_folder() / L"DispatcherKernel.cso" };
    ComputePipelineStateDefinition DispatcherKernelStateDef{
        .RootSignature = &DispatcherKernelSignature,
        .ComputeShader = &DispatcherKernelCS
    };
    auto DispatcherKernel = pipelineStateProvider.CreatePipelineStateAsync(DispatcherKernelStateDef).get();

    RootSignature<ConcurrentBinaryTreeRootDesc> SubdivisionSignature{ device };
    ComputeShader SubdivisionKernelCS{ app_folder() / L"SubdivisionKernel.cso" };
    ComputePipelineStateDefinition SubdivisionKernelStateDef{
        .RootSignature = &SubdivisionSignature,
        .ComputeShader = &SubdivisionKernelCS
    };
    auto SubdivisionKernel = pipelineStateProvider.CreatePipelineStateAsync(SubdivisionKernelStateDef).get();

    RootSignature<ConcurrentBinaryTreeRootDesc> SumReductionSignature{ device };
    ComputeShader SumReductionKernelCS{ app_folder() / L"SumReductionKernel.cso" };
    ComputePipelineStateDefinition SumReductionKernelStateDef{
        .RootSignature = &SumReductionSignature,
        .ComputeShader = &SumReductionKernelCS
    };
    auto SumReductionKernel = pipelineStateProvider.CreatePipelineStateAsync(SumReductionKernelStateDef).get();
    //Init hull shader

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
    std::filesystem::path fPath =
        //app_folder() / L"27_987_86_925_6_8_8.png";
        //app_folder() / L"47_473_19_062_15_100_100.png";
        //app_folder() / L"27_985_86_924_10_250_250.png";
        //app_folder() / L"27_985_86_924_10_500_250.png";
        app_folder() / L"27_985_86_924_10_500_500.png";
        //app_folder() / L"27_985_86_924_10_1000_500.png";
        //app_folder() / L"27_985_86_924_10_1000_1000.png";
        //app_folder() / L"27_985_86_924_10_2000_1000.png";
        //app_folder() / L"27_985_86_924_10_2000_2000.png";
        ////app_folder() / L"27_985_86_924_10_4000_4000.png";
    // Creation of meshlets
    auto heights = ImmutableTexture::readTextureData(fPath);

	// Width, Height
    float MeshletSize[2];
    MeshletSize[0] = 2.0f;
    MeshletSize[1] = 2.0f;

    ImmutableTexture texture{ immutableAllocationContext, fPath };

    groupedResourceAllocator.Build();

    auto mutableAllocationContext = immutableAllocationContext;
    CommittedResourceAllocator committedResourceAllocator{ device };
    mutableAllocationContext.ResourceAllocator = &committedResourceAllocator;

    // Mutable Mesh
    BisectorMesh mainmesh = BisectorMesh::CreateQuad(mutableAllocationContext);

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
    io.DisplayFramebufferScale = { dpi, dpi };

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
#pragma endregion

#pragma region BitField Buffer

    // Create Buffer for bitfield
    BufferRef buffer = mutableAllocationContext
        .ResourceAllocator->CreateBuffer(BufferDefinition(4 * sizeof(UINT32), BufferFlags::UnorderedAccess));

    D3D12_BUFFER_SRV srvbufDesc = {};
    srvbufDesc.NumElements = 4;
    srvbufDesc.StructureByteStride = sizeof(UINT32);
    srvbufDesc.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

    D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};
    srvdesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
    srvdesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
    srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvdesc.Buffer = srvbufDesc;

    D3D12_BUFFER_UAV uavbufDesc = {};
    uavbufDesc.CounterOffsetInBytes = 0;
    uavbufDesc.NumElements = 4;
    uavbufDesc.StructureByteStride = sizeof(UINT32);
    uavbufDesc.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

    D3D12_UNORDERED_ACCESS_VIEW_DESC uavdesc = {};
    uavdesc.Format = DXGI_FORMAT_UNKNOWN;
    uavdesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
    uavdesc.Buffer = uavbufDesc;


    StructuredObjectViews objview{ mutableAllocationContext,buffer.get(), BufferViewDefinitions{
        .ShaderResource = srvdesc,
        .UnorderedAccess = uavdesc // Behelyetesítendõ
    } };

#pragma endregion


    // Camera setup
    bool firstperson = false;
    bool divideTry = false;
    bool mergeTry = false;
    bool highlightTry = false;
    bool resetTri = false;
    bool& quit = m_windowClosed;
    Camera cam;

    // Event setup
    // SetupEvents(window);
    window.KeyDown([&cam, &quit, &firstperson, &divideTry, &resetTri](CoreWindow const&,
        KeyEventArgs const& args) {
            if (ImGui::GetIO().WantCaptureKeyboard)
                return;
            switch (args.VirtualKey()) {
            case Windows::System::VirtualKey::Escape:
                quit = true;
                break;

            case Windows::System::VirtualKey::R:
                resetTri = true;
                break;

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
    window.PointerPressed(
        [&divideTry, &mergeTry, &highlightTry](CoreWindow const&, PointerEventArgs const& args)
        {
            auto props = args.CurrentPoint().Properties();
            if (props.IsLeftButtonPressed())
                divideTry = true;
            if (props.IsRightButtonPressed())
                mergeTry = true;
            if (props.IsMiddleButtonPressed())
            {
	            highlightTry = !highlightTry;
            }
        });

    while (!m_windowClosed)
    {
        // Event Handlers
        if (divideTry)
        {
            divideTry = false;
            if (focusedTriId != -1)
            {
                cbt.ConformingSplit(focusedTriId);
            }
        }

        if (mergeTry)
        {
            mergeTry = false;
            if (focusedTriId != -1)
            {
                cbt.ConformingMerge(focusedTriId);
            }
        }

        if (highlightTry)
        {
            highlightID = cbt.GetTrueNeighbour(focusedTriId);
        }
        else
        {
            highlightID = { 0,0,0,0 };
        }

        if (resetTri)
        {
            resetTri = false;
        }
        //

        //Process user input
        dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

        //Get frame resources
        auto& resources = frames[i++ & 0x1u];
        auto renderTargetView = swapChain.RenderTargetView();

        //Wait until buffers can be reused
        if (resources.Marker) resources.Fence.Await(resources.Marker);

        // ImGui
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplUwp_NewFrame();
        ImGui::NewFrame();
        // -----

        ImGuiCommands(cam, simplePipelineStateDefinition, wireFrameStateDefinition, simplePipelineState, pipelineStateProvider);

        // ImGui Rendering
        ImGui::Render();

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

            XMStoreFloat4x4(&constants.WorldViewProjection, worldViewProjection);
            XMStoreUInt2(&constants.MeshletSize, XMVECTOR{ MeshletSize[0],MeshletSize[1] });
            XMStoreFloat(&constants.MapSize, XMVECTOR{ MapWH });
            XMStoreFloat(&constants.MaxHeight, XMVECTOR{ MaxHeight });
            XMStoreFloat(&constants.tessFactorFloat, XMVECTOR{ tessFact });
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

        //CBT steps
        {
            //DispatcherKernel
            {
                auto mask = DispatcherKernelSignature.Set(allocator, RootSignatureUsage::Compute);
                mask.uavTest = *objview.UnorderedAccess();
                DispatcherKernel.Apply(allocator);

                allocator.Dispatch();

                allocator.UAVResourceBarrier(buffer.get()->get());
            }
            //SubdivisionKernel
            {
                auto mask = SubdivisionSignature.Set(allocator, RootSignatureUsage::Compute);
                mask.uavTest = *objview.UnorderedAccess();
                SubdivisionKernel.Apply(allocator);

                allocator.Dispatch();

                allocator.UAVResourceBarrier(buffer.get()->get());
            }
            //SumReductionKernel
            {
                auto mask = SumReductionSignature.Set(allocator, RootSignatureUsage::Compute);
                mask.uavTest = *objview.UnorderedAccess();
                SumReductionKernel.Apply(allocator);

                allocator.Dispatch();

                allocator.UAVResourceBarrier(buffer.get()->get());
            }
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

        //End frame command list
        {
            allocator.TransitionResource(*renderTargetView, ResourceStates::RenderTarget, ResourceStates::Present);
            auto drawCommandList = allocator.EndList();

            allocator.BeginList();
            resources.DynamicBuffer.UploadResources(allocator);
            resourceUploader.UploadResourcesAsync(allocator);
            auto initCommandList = allocator.EndList();

            directQueue.get()->Execute(initCommandList);
            directQueue.get()->Execute(drawCommandList);
            resources.Marker = resources.Fence.EnqueueSignal(*directQueue.get());
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
