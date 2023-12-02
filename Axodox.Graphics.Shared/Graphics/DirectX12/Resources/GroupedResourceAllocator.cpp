#include "pch.h"
#include "GroupedResourceAllocator.h"

using namespace std;
using namespace winrt;

namespace Axodox::Graphics::D3D12
{
  void GroupedResourceAllocator::AllocateResources(ResourceSpan resources)
  {
    //Get allocation info & flags
    D3D12_RESOURCE_ALLOCATION_INFO allocationInfo;
    D3D12_HEAP_FLAGS heapFlags;
    {
      bool hasBuffers = false;
      bool hasTextures = false;
      bool hasTargets = false;

      vector<D3D12_RESOURCE_DESC> descriptions;
      descriptions.reserve(resources.size());
      for (auto& resource : resources)
      {
        auto& description = resource->Description();

        if (description.Dimension == D3D12_RESOURCE_DIMENSION_BUFFER)
        {
          hasBuffers = true;
        }
        else
        {
          if (description.Flags & (D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET | D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL))
          {
            hasTargets = true;
          }
          else
          {
            hasTextures = true;
          }
        }
        
        descriptions.push_back(description);        
      }

      allocationInfo = _device->GetResourceAllocationInfo(0, uint32_t(descriptions.size()), descriptions.data());

      heapFlags = D3D12_HEAP_FLAG_CREATE_NOT_ZEROED;
      if (!hasBuffers) heapFlags |= D3D12_HEAP_FLAG_DENY_BUFFERS;
      if (!hasTextures) heapFlags |= D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES;
      if (!hasTargets) heapFlags |= D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES;
    }

    //Check if we need to create the heap
    bool isCreatingNewHeap;
    if (_heap)
    {
      auto description = _heap->GetDesc();
      isCreatingNewHeap = 
        description.Alignment % allocationInfo.Alignment != 0 ||
        description.SizeInBytes < allocationInfo.SizeInBytes ||
        description.Flags != heapFlags;
    }
    else
    {
      isCreatingNewHeap = true;
    }

    //Create new heap if needed
    if (isCreatingNewHeap)
    {
      D3D12_HEAP_DESC description{
        .SizeInBytes = allocationInfo.SizeInBytes,
        .Properties = {
          .Type = D3D12_HEAP_TYPE_DEFAULT,
          .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
          .MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
          .CreationNodeMask = 0,
          .VisibleNodeMask = 0
        },
        .Alignment = allocationInfo.Alignment,
        .Flags = heapFlags
      };

      check_hresult(_device->CreateHeap(&description, IID_PPV_ARGS(_heap.put())));
    }
  }
}