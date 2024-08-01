#pragma once
#include "Texture.h"
#include "ResourceAllocationContext.h"

namespace Axodox::Graphics::D3D12
{
  class AXODOX_GRAPHICS_API ImmutableTexture
  {
  public:
    ImmutableTexture(const ResourceAllocationContext& context, const std::filesystem::path& path);
    static std::vector<std::vector<float>> readTextureData(const std::filesystem::path& path)
    {
      std::vector<std::vector<float>> heights;
      auto textureData = TextureData::FromFile(path);
      auto buf = textureData.AsRawSpan();

      float min = 0.0f, max = 255.0f;

      for (int i = 0; i < textureData.Header().Height; i++)
      {
        heights.push_back(std::vector<float>());
      }

      int cnt = 0;
      for (const auto &e : buf)
      {
        if ((cnt % 4) == 0)
        {
          float normalized = ((e - min) / (max - min)) * 8.0f;
          heights.at(cnt / 400).push_back(normalized);
        }
        cnt++;
      }
      return heights;
    }

    operator GpuVirtualAddress() const;

  private:
    TextureRef _texture;
    ShaderResourceViewRef _view;
    Infrastructure::event_subscription _allocatedSubscription;
  };
}