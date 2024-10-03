#pragma once
#include "../Resources/ResourceAllocationContext.h"
#include "MeshDescriptions.h"

using namespace Axodox::Infrastructure;
using namespace std;

namespace Axodox::Graphics::D3D12
{
  class AXODOX_GRAPHICS_API ImmutableMesh
  {
  public:
    ImmutableMesh(const ResourceAllocationContext& context, MeshDescription&& description);

    void Draw(CommandAllocator& allocator, uint32_t instanceCount = 1);

    void LineRender(bool b) 
    {
      _topology = b ? 
        D3D12_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST :
        D3D12_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    }

    void setNewMesh(const ResourceAllocationContext& context, MeshDescription&& description)
    {      
      if (_vertexBuffer)
      {
        _verticesAllocatedSubscription = _vertexBuffer->Allocated([this, buffer = move(description.Vertices), context](Resource* resource) {
          context.ResourceUploader->EnqueueUploadTask(resource, &buffer);
          _vertexBufferView = { (*resource)->GetGPUVirtualAddress(), buffer.ByteCount(), buffer.ItemSize() };
          });
      }

      if (_indexBuffer)
      {
        _indicesAllocatedSubscription = _indexBuffer->Allocated([this, buffer = move(description.Indices), context](Resource* resource) {
          context.ResourceUploader->EnqueueUploadTask(resource, &buffer);
          _indexBufferView = { (*resource)->GetGPUVirtualAddress(), buffer.ByteCount(), GetIndexFormat(buffer.ItemSize()) };
          });
      }
    }

  private:
    BufferRef _vertexBuffer;
    BufferRef _indexBuffer;

    Infrastructure::event_subscription _verticesAllocatedSubscription, _indicesAllocatedSubscription;

    D3D12_PRIMITIVE_TOPOLOGY _topology;
    uint32_t _vertexCount, _indexCount;
    std::optional<D3D12_VERTEX_BUFFER_VIEW> _vertexBufferView;
    std::optional<D3D12_INDEX_BUFFER_VIEW> _indexBufferView;

    static DXGI_FORMAT GetIndexFormat(uint32_t size);
  };
}