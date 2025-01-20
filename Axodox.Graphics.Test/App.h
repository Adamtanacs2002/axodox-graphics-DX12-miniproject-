#pragma once

// ImGUI
#include "DrawPrimitivesUtil.h"
#include <format>


#include <winrt/Windows.Graphics.Display.h>
// -----

#include "Camera.h"
#include "CbtCPU.h"

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

#pragma region RootDescriptors

struct SimpleRootDescription : public RootSignatureMask
{
    RootDescriptor<RootDescriptorType::ConstantBuffer> ConstantBuffer;
    RootDescriptorTable<1> Texture;
    StaticSampler Sampler;

    SimpleRootDescription(const RootSignatureContext& context) :
        RootSignatureMask(context),
        ConstantBuffer(this, { 0 }, ShaderVisibility::All),
        Texture(this, { DescriptorRangeType::ShaderResource }, ShaderVisibility::All),
        Sampler(this, { 0 }, Filter::Linear, TextureAddressMode::Clamp, ShaderVisibility::All)
    {
        Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
};

struct ConcurrentBinaryTreeRootDesc : public RootSignatureMask
{
    RootDescriptorTable<1> uavTest;
    ConcurrentBinaryTreeRootDesc(const RootSignatureContext& context) :
        RootSignatureMask(context),
        uavTest(this, { DescriptorRangeType::UnorderedAccess, 1 })
    {
        Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
};

struct PostProcessingRootDescription : public RootSignatureMask
{
    RootDescriptor<RootDescriptorType::ConstantBuffer> ConstantBuffer;
    RootDescriptorTable<1> uavTest;
    RootDescriptorTable<1> InputTexture;
    RootDescriptorTable<1> OutputTexture;
    StaticSampler Sampler;

    PostProcessingRootDescription(const RootSignatureContext& context) :
        RootSignatureMask(context),
        ConstantBuffer(this, { 0 }),
        uavTest(this, { DescriptorRangeType::UnorderedAccess, 1 }),
        InputTexture(this, { DescriptorRangeType::ShaderResource }),
        OutputTexture(this, { DescriptorRangeType::UnorderedAccess }),
        Sampler(this, { 0 }, Filter::Linear, TextureAddressMode::Clamp)
    {
        Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
};

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

#pragma endregion

struct vertexDemo
{
    ImVec2 pos;
    int index;
};

struct App : public implements<App, IFrameworkViewSource, IFrameworkView>
{
private:

	#pragma region UWP

    CoreWindow window;
    CoreDispatcher dispatcher;

	#pragma endregion

	#pragma region DX12

    GraphicsDevice device{};
    shared_ptr<CommandQueue> directQueue;

	#pragma endregion

    unsigned int i = 0u;
    int depth = 0;
    bool isLineDraw = false;
    float MapWH = 100.0f;
    float MaxHeight = 6.0f;
    float tessFact = 2.0f;

    // CBT
    CbtCPU cbt = {};

    // ImGui
    bool highlighted = false;
    std::array<int, 4> highlightID = { 0,0,0,0 };
    uint32_t focusedTriId = 0;
    std::vector<vertexDemo> vertexBuffer = {};
    vector<uint32_t> idList = {};
    std::vector<ColoredTri> triList = {};
    ColoredTri BaseTri = {
      .p0 = new ImVec2(50.0f,100.0f),
      .p1 = new ImVec2(50.0f,250.0f),
      .p2 = new ImVec2(200.0f,250.0f),
      .col = ImColor(ImVec4(0.323f,0.475f,0.615f,1.0f))
    };
    DirectX::XMFLOAT4 clear_color = { 0.05f, 0.25f, 0.60f, 1.00f };
    ImColor depthColor[5] = {
    ImColor(ImVec4(0.970f, 0.0582f, 0.058f, 1.0f)),
    ImColor(ImVec4(0.104f, 0.0582f, 0.970f, 1.0f)),
    ImColor(ImVec4(0.304f, 0.2582f, 0.670f, 1.0f)),
    ImColor(ImVec4(0.904f, 0.6582f, 0.670f, 1.0f)),
    ImColor(ImVec4(0.104f, 0.9270f, 0.058f, 1.0f))
    };

public:

    App();
    void InitWindow();

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

    void SetWindow(CoreWindow const& window)
    {
    }

    void ImGuiCommands(Camera& cam, GraphicsPipelineStateDefinition& simplePipelineStateDefinition, GraphicsPipelineStateDefinition&
                       wireFrameStateDefinition, PipelineState& simplePipelineState, PipelineStateProvider pipelineStateProvider);
    void Run();

    struct Constants
    {
        XMFLOAT4X4 WorldViewProjection;
        XMUINT2 MeshletSize;
        float MapSize;
        float MaxHeight;
        float disFromEye;
        float tessFactorFloat;
    };

	#pragma region ImGui Constants

    static int const NUM_BACK_BUFFERS = 3;
    static const int NUM_FRAMES_IN_FLIGHT = 3;
    bool m_windowClosed = false;
    com_ptr<ID3D12DescriptorHeap> m_pd3dRtvDescHeap;
    com_ptr<ID3D12DescriptorHeap> m_pd3dSrvDescHeap;

	#pragma endregion
};