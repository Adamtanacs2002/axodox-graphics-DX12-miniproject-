#pragma once
#include "../Resources/ResourceAllocationContext.h"
#include "MeshDescriptions.h"

namespace Axodox::Graphics::D3D12
{
  class AXODOX_GRAPHICS_API ImmutableMesh
  {
  public:
    ImmutableMesh(const ResourceAllocationContext& context, MeshDescription& description);

    void Draw(CommandAllocator& allocator, uint32_t instanceCount = 1);

    void LineRender(bool b) 
    {
      _topology = b ? 
        D3D12_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST :
        D3D12_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    }

    D3D12_VERTEX_BUFFER_VIEW GetVBV()
    {
      if (!_vertexBufferView.has_value())
      {
        throw std::exception("No value assigned");
      }
      return (D3D12_VERTEX_BUFFER_VIEW)_vertexBufferView.value();
    };
    D3D12_INDEX_BUFFER_VIEW GetIBV()
    {
      if (!_indexBufferView.has_value())
      {
        throw std::exception("No value assigned");
      }
      return (D3D12_INDEX_BUFFER_VIEW)_indexBufferView.value();
    };
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