#include "pch.h"
#include "GraphicsDevice.h"

using namespace Axodox::Infrastructure;
using namespace winrt;

namespace Axodox::Graphics::D3D12
{
  GraphicsDevice::GraphicsDevice(ID3D12DeviceChild* deviceChild)
  { 
    check_hresult(deviceChild->GetDevice(guid_of<ID3D12DeviceT>(), _device.put_void()));
  }

  GraphicsDevice::GraphicsDevice(D3D_FEATURE_LEVEL featureLevel)
  {
#ifdef _DEBUG
    com_ptr<ID3D12Debug> debug;
    check_hresult(D3D12GetDebugInterface(guid_of<ID3D12Debug>(), debug.put_void()));
    debug->EnableDebugLayer();
#endif

    check_hresult(D3D12CreateDevice(
      nullptr,
      featureLevel,
      guid_of<ID3D12DeviceT>(),
      _device.put_void()));
  }

  ID3D12DeviceT* GraphicsDevice::get() const
  {
    return _device.get();
  }

  ID3D12DeviceT* GraphicsDevice::operator->() const
  {
    return _device.get();
  }

  CapabilityFlags GraphicsDevice::Capabilities()
  {
    if (_flags == CapabilityFlags::Unknown)
    {
      _flags = CapabilityFlags::None;

      D3D12_FEATURE_DATA_ARCHITECTURE1 architecture;
      check_hresult(_device->CheckFeatureSupport(D3D12_FEATURE_ARCHITECTURE1, &architecture, sizeof(D3D12_FEATURE_DATA_ARCHITECTURE1)));

      set_flag(_flags, CapabilityFlags::IsUniformMemoryAccess, architecture.UMA);
    }

    return _flags;
  }

  MemoryPool GraphicsDevice::VideoMemoryPool()
  {
    return has_flag(Capabilities(), CapabilityFlags::IsUniformMemoryAccess) ? MemoryPool::SystemMemory : MemoryPool::VideoMemory;
  }
}
