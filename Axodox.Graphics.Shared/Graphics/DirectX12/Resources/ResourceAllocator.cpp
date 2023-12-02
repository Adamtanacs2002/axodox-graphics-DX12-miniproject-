#include "pch.h"
#include "ResourceAllocator.h"

using namespace std;

namespace Axodox::Graphics::D3D12
{
  ResourceAllocator::ResourceAllocator(const GraphicsDevice& device) :
    _device(device)
  { }

  resource_ptr ResourceAllocator::CreateTexture(const TextureDefinition& definition)
  {
    return AddResource(D3D12_RESOURCE_DESC(definition));
  }

  resource_ptr ResourceAllocator::CreateBuffer(const BufferDefinition& definition)
  {
    return AddResource(D3D12_RESOURCE_DESC(definition));
  }

  resource_ptr ResourceAllocator::AddResource(const D3D12_RESOURCE_DESC& description)
  {
    auto allocationInfo = _device->GetResourceAllocationInfo(0, 1, &description);

    auto resource = make_unique<Resource>(
      this, 
      description, 
      allocationInfo.SizeInBytes, 
      allocationInfo.Alignment
    );

    auto result = resource_ptr(resource.get());

    lock_guard lock(_mutex);
    _resources.push_back(move(resource));
    _isDirty = true;

    return result;
  }

  void ResourceAllocator::DeleteResource(const Resource* resource)
  {
    lock_guard lock(_mutex);
    _reclaimables.emplace(resource);
    _isDirty = true;
  }

  void ResourceAllocator::Build()
  {
    //Check dirty flag
    if (!_isDirty) return;

    //Clean resource references
    Clean();

    //Allocate resources
    AllocateResources(_resources);
  }

  void ResourceAllocator::Clean()
  {
    lock_guard lock(_mutex);

    for (auto i = 0; i < _resources.size(); i++)
    {
      auto& item = _resources[i];
      if (_reclaimables.contains(item.get()))
      {
        swap(_resources[i--], _resources.back());
        _resources.pop_back();
      }
    }

    _reclaimables.clear();
  }
}