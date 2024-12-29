#pragma once
#include "Resource.h"
#include "BufferDefinition.h"

namespace Axodox::Graphics::D3D12
{
  /// <summary>
  /// Resource object, holding data to create buffer.
  /// </summary>
  class AXODOX_GRAPHICS_API Buffer : public Resource
  {
    friend class ResourceAllocator;

  public:
    /// <summary>
    /// Constructor for Buffer.
    /// </summary>
    /// <param name="device">Graphics device object.</param>
    /// <param name="definition">Definition of the constructed buffer.</param>
    Buffer(const GraphicsDevice& device, const BufferDefinition& definition);
    /// <summary>
    /// Constructor for Buffer. (using Resource)
    /// </summary>
    /// <param name="resource">COM pointer to a ID3D12Resource object.</param>
    Buffer(const winrt::com_ptr<ID3D12Resource>& resource);

    /// <summary>
    /// Returns the definition of the Buffer.
    /// </summary>
    /// <returns>BufferDefinition struct.</returns>
    const BufferDefinition& Definition() const;
    /// <summary>
    /// Virtual function override from Resource class. Returns a DX12 description of buffer.
    /// </summary>
    /// <returns>D3D12_RESOURCE_DESC object created from _definition.</returns>
    virtual D3D12_RESOURCE_DESC Description() const override;
    /// <summary>
    /// Virtual function override from Resource class. Returns a DX12 state of buffer.
    /// </summary>
    /// <returns>D3D12_RESOURCE_STATE_COMMON</returns>
    virtual D3D12_RESOURCE_STATES DefaultState() const override;
    /// <summary>
    /// Virtual function override from Resource class. Returns a DX12 clear value of buffer.
    /// </summary>
    /// <returns>Nullopt</returns>
    virtual std::optional<D3D12_CLEAR_VALUE> DefaultClearValue() const override;

  protected:
    /// <summary>
    /// General protected constructor for Buffer.
    /// </summary>
    /// <param name="definition">Definition of the constructed buffer.</param>
    Buffer(const BufferDefinition& definition);

  private:
    /// <summary>
    /// Struct defining the Buffer properties.
    /// </summary>
    BufferDefinition _definition;
  };

  /// <summary>
  /// Resource pointer for Buffer.
  /// </summary>
  using BufferRef = resource_ptr<Buffer>;
}