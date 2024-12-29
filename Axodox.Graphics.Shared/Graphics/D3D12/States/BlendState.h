#pragma once
#include "pch.h"

namespace Axodox::Graphics::D3D12
{
  enum BlendType : uint8_t
  {
    Opaque,
    Additive,
    Subtractive,
    AlphaBlend,
    Minimum,
    Maximum
  };

  struct AXODOX_GRAPHICS_API BlendState
  {
    /// <summary>
    /// Array containing all BlendType types.
    /// </summary>
    std::array<BlendType, 8> BlendTypes;

    /// <summary>
    /// Basic constructor for a single render target.
    /// </summary>
    /// <param name="blendType">BlendType of the render target.</param>
    BlendState(BlendType blendType = BlendType::Opaque);
    /// <summary>
    /// Constructor for multiple render target, using BlendStates.
    /// </summary>
    /// <param name="blendTypes">List of all used BlendTypes.</param>
    BlendState(std::initializer_list<BlendType> blendTypes);

    /// <summary>
    /// Returns all render targets blend description in a D3D12_BLEND_DESC object.
    /// </summary>
    explicit operator D3D12_BLEND_DESC() const;
  };
}