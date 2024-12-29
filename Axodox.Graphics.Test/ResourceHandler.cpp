#include "pch.h"
#include "ResourceHandler.h"

using namespace Axodox::Graphics::D3D12;

StructuredObjectViews ResourceHandler::CreateBufferWithViews(
  ResourceAllocationContext mutableAllocationContext
)
{
  BufferRef buffer = mutableAllocationContext
    .ResourceAllocator->CreateBuffer(BufferDefinition(4 * sizeof(UINT64), BufferFlags::UnorderedAccess));

  D3D12_BUFFER_SRV srvbufDesc = {};
  srvbufDesc.NumElements = 4;
  srvbufDesc.StructureByteStride = sizeof(UINT64);
  srvbufDesc.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

  D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc = {};
  srvdesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
  srvdesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
  srvdesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  srvdesc.Buffer = srvbufDesc;

  D3D12_BUFFER_UAV uavbufDesc = {};
  uavbufDesc.CounterOffsetInBytes = 0;
  uavbufDesc.NumElements = 4;
  uavbufDesc.StructureByteStride = sizeof(UINT64);
  uavbufDesc.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

  D3D12_UNORDERED_ACCESS_VIEW_DESC uavdesc = {};
  uavdesc.Format = DXGI_FORMAT_UNKNOWN;
  uavdesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
  uavdesc.Buffer = uavbufDesc;


  StructuredObjectViews objview{ mutableAllocationContext,buffer.get(), BufferViewDefinitions{
      .ShaderResource = srvdesc,
      .UnorderedAccess = uavdesc // Behelyetesítendõ
  } };

  return objview;
}
