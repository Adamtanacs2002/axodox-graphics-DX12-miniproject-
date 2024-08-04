#include "pch.h"
#include "Primitives.h"

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace std;

namespace Axodox::Graphics::D3D12
{
  MeshDescription CreateQuad(float size)
  {
    static const XMBYTEN4 normal{ 0.f, 0.f, 1.f, 1.f };
    size = size / 2;

    MeshDescription result;

    result.Vertices = {
      VertexPositionNormalTexture{ XMFLOAT3{-size, size, 0.f}, normal, XMUSHORTN2{0.f, 0.f} },
      VertexPositionNormalTexture{ XMFLOAT3{-size, -size, 0.f}, normal, XMUSHORTN2{0.f, 1.f} },
      VertexPositionNormalTexture{ XMFLOAT3{size, size, 0.f}, normal, XMUSHORTN2{1.f, 0.f} },
      VertexPositionNormalTexture{ XMFLOAT3{size, -size, 0.f}, normal, XMUSHORTN2{1.f, 1.f} }
    };

    result.Indices = { 0, 1, 2, 1, 3, 2 };
    result.Topology = PrimitiveTopology::TriangleList;

    return result;
  }

  MeshDescription CreateCube(float size, bool useSameTextureOnAllFaces)
  {
    MeshDescription result;
    size = size / 2;

    //Vertices
    VertexPositionNormalTexture* pVertex;
    result.Vertices = BufferData(24, pVertex);

    float textureStep = 1.f / 6.f, textureStart = 0.f, textureEnd = 1.f;
    XMBYTEN4 normal;

    normal = XMBYTEN4{ 0.f, 0.f, -1.f, 1.f };
    if (!useSameTextureOnAllFaces) textureEnd = textureStart + textureStep;
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, size, -size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, -size, -size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, -size, -size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, size, -size}, normal, XMUSHORTN2{textureStart, 0.f} };

    normal = XMBYTEN4{ 1.f, 0.f, 0.f, 1.f };
    if (!useSameTextureOnAllFaces) { textureStart = textureEnd; textureEnd = textureStart + textureStep; }
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, -size, -size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, size, -size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, size, size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, -size, size}, normal, XMUSHORTN2{textureStart, 0.f} };

    normal = XMBYTEN4{ 0.f, 1.f, 0.f, 1.f };
    if (!useSameTextureOnAllFaces) { textureStart = textureEnd; textureEnd = textureStart + textureStep; }
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, size, -size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, size, -size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, size, size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{size, size, size}, normal, XMUSHORTN2{textureStart, 0.f} };

    normal = XMBYTEN4{ -1.f, 0.f, 0.f, 1.f };
    if (!useSameTextureOnAllFaces) { textureStart = textureEnd; textureEnd = textureStart + textureStep; }
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, size, -size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, -size, -size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, -size, size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{-size, size, size}, normal, XMUSHORTN2{textureStart, 0.f} };

    normal = XMBYTEN4{ 0.f, -1.f, 0.f, 1.f };
    if (!useSameTextureOnAllFaces) { textureStart = textureEnd; textureEnd = textureStart + textureStep; }
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ -size, -size, -size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ size, -size, -size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ size, -size, size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ -size, -size, size}, normal, XMUSHORTN2{textureStart, 0.f} };

    normal = XMBYTEN4{ 0.f, 0.f, 1.f, 1.f };
    if (!useSameTextureOnAllFaces) { textureStart = textureEnd; textureEnd = textureStart + textureStep; }
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ size, -size, size}, normal, XMUSHORTN2{textureStart, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ size, size, size}, normal, XMUSHORTN2{textureEnd, 1.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ -size, size, size}, normal, XMUSHORTN2{textureEnd, 0.f} };
    *pVertex++ = VertexPositionNormalTexture{ XMFLOAT3{ -size, -size, size}, normal, XMUSHORTN2{textureStart, 0.f} };

    //Indices
    uint32_t* pIndex;
    result.Indices = BufferData(36, pIndex);

    for (auto side = 0u; side < 6u; side++)
    {
      uint32_t index = side * 4u;
      *pIndex++ = index;
      *pIndex++ = index + 1;
      *pIndex++ = index + 2;
      *pIndex++ = index + 2;
      *pIndex++ = index + 3;
      *pIndex++ = index;
    }

    //Topology
    result.Topology = PrimitiveTopology::TriangleList;

    return result;
  }

  MeshDescription CreatePlane(float size, DirectX::XMUINT2 subdivisions)
  {
    if (subdivisions.x < 2 || subdivisions.y < 2) throw logic_error("Plane size must be at least 2!");
    if (subdivisions.x * subdivisions.y > (uint64_t)numeric_limits<uint32_t>::max() + 1) throw logic_error("Run out of indices!");

    MeshDescription result;

    //Vertices
    float xstep = size / (subdivisions.x - 1), xtexstep = 1.f / (subdivisions.x - 1), xstart = -size / 2.f;
    float ystep = size / (subdivisions.y - 1), ytexstep = 1.f / (subdivisions.y - 1), ystart = -size / 2.f;
    uint32_t vertexCount = subdivisions.x * subdivisions.y;

    VertexPositionNormalTexture* pVertex;
    result.Vertices = BufferData(vertexCount, pVertex);

    for (uint32_t j = 0; j < subdivisions.y; j++)
    {
      for (uint32_t i = 0; i < subdivisions.x; i++)
      {
        *pVertex++ = {
          XMFLOAT3{ xstart + i * xstep, ystart + j * ystep, 0.f },
          XMBYTEN4{ 0.f, 0.f, 1.f, 1.f },
          XMUSHORTN2{ i * xtexstep, 1 - j * ytexstep }
          };
      }
    }

    //Indices
    uint32_t triangleWidth = subdivisions.x - 1, triangleHeight = subdivisions.y - 1;
    uint32_t indexCount = triangleWidth * triangleHeight * 6;

    uint32_t* pIndex;
    result.Indices = BufferData(indexCount, pIndex);

    for (uint32_t j = 0; j < triangleHeight; j++)
    {
      for (uint32_t i = 0; i < triangleWidth; i++)
      {
        *pIndex++ = j * subdivisions.x + i;
        *pIndex++ = j * subdivisions.x + i + 1;
        *pIndex++ = (j + 1) * subdivisions.x + i;
        *pIndex++ = j * subdivisions.x + i + 1;
        *pIndex++ = (j + 1) * subdivisions.x + i + 1;
        *pIndex++ = (j + 1) * subdivisions.x + i;
      }
    }

    //Topology
    result.Topology = PrimitiveTopology::TriangleList;

    return result;
  }

  MeshDescription CreateWholeMap(std::vector<std::vector<float>> heights, 
    std::vector<XMUINT2>* meshletcoords)
  {
    int subdivisionsX = heights.at(0).size();
    int subdivisionsY = heights.size();
    float size = 10.0f;
    if (subdivisionsX < 2 || subdivisionsY < 2) throw logic_error("Plane size must be at least 2!");
    if (subdivisionsX * subdivisionsY > (uint64_t)numeric_limits<uint32_t>::max() + 1) throw logic_error("Run out of indices!");

    MeshDescription result;

    //Vertices
    float xstep = size / (subdivisionsX - 1), xtexstep = 1.f / (subdivisionsX - 1), xstart = -size / 2.f;
    float ystep = size / (subdivisionsY - 1), ytexstep = 1.f / (subdivisionsY - 1), ystart = -size / 2.f;
    uint32_t vertexCount = subdivisionsX * subdivisionsY;

    VertexPositionNormalTexture* pVertex;
    result.Vertices = BufferData(vertexCount, pVertex);

    for (uint32_t j = 0; j < subdivisionsY; j++)
    {
      std::vector<XMFLOAT3> tmp;
      for (uint32_t i = 0; i < subdivisionsX; i++)
      {
        *pVertex++ = {
          XMFLOAT3{ xstart + i * xstep, ystart + j * ystep, heights.at(i).at(j) - 6.f},
          XMBYTEN4{ 0.f, 0.f, 1.f, 1.f },
          // XMUBYTEN4{ 0.0f, 0.33f, 0.33f, 1.0f}
          XMUSHORTN2{j * ytexstep, i * xtexstep }
        };
        tmp.push_back(XMFLOAT3{ xstart + i * xstep, ystart + j * ystep, heights.at(i).at(j) - 8.f });
        meshletcoords->push_back({ i / 8,j / 8 });
      }
    }

    //Indices
    uint32_t triangleWidth = subdivisionsX - 1, triangleHeight = subdivisionsY - 1;
    uint32_t indexCount = triangleWidth * triangleHeight * 6;

    uint32_t* pIndex;
    result.Indices = BufferData(indexCount, pIndex);

    for (uint32_t j = 0; j < triangleHeight; j++)
    {
      for (uint32_t i = 0; i < triangleWidth; i++)
      {
        *pIndex++ = j * subdivisionsX + i;
        *pIndex++ = j * subdivisionsX + i + 1;
        *pIndex++ = (j + 1) * subdivisionsX + i;
        *pIndex++ = j * subdivisionsX + i + 1;
        *pIndex++ = (j + 1) * subdivisionsX + i + 1;
        *pIndex++ = (j + 1) * subdivisionsX + i;
      }
    }

    //Topology
    result.Topology = PrimitiveTopology::TriangleList;

    return result;
  }

  //MeshDescription CreateMeshlet(Meshlet meshlet)
  //{
  //  auto size = 1.0f;
  //  DirectX::XMUINT2 subdivisions = { sizeof(meshlet.vertices[0]) / sizeof(meshlet.vertices[0][0]),sizeof(meshlet.vertices) / sizeof(meshlet.vertices[0])};
  //  if (subdivisions.x < 2 || subdivisions.y < 2) throw logic_error("Plane size must be at least 2!");
  //  if (subdivisions.x * subdivisions.y > (uint64_t)numeric_limits<uint32_t>::max() + 1) throw logic_error("Run out of indices!");

  //  MeshDescription result;

  //  //Vertices
  //  float xstep = size / (subdivisions.x - 1), xtexstep = 1.f / (subdivisions.x - 1), xstart = meshlet.pos.x + -size / 2.f;
  //  float ystep = size / (subdivisions.y - 1), ytexstep = 1.f / (subdivisions.y - 1), ystart = meshlet.pos.y + -size / 2.f;
  //  uint32_t vertexCount = subdivisions.x * subdivisions.y;

  //  VertexPositionNormalTexture* pVertex;
  //  result.Vertices = BufferData(vertexCount, pVertex);

  //  for (uint32_t j = 0; j < subdivisions.y; j++)
  //  {
  //    for (uint32_t i = 0; i < subdivisions.x; i++)
  //    {
  //      *pVertex++ = {
  //        XMFLOAT3{ xstart + i * xstep, ystart + j * ystep, 0.f + meshlet.vertices[j][i].attitude},
  //        XMBYTEN4{ 0.f, 0.f, 1.f, 1.f },
  //        XMUSHORTN2{ i * xtexstep, 1 - j * ytexstep }
  //      };
  //    }
  //  }

  //  //Indices
  //  uint32_t triangleWidth = subdivisions.x - 1, triangleHeight = subdivisions.y - 1;
  //  uint32_t indexCount = triangleWidth * triangleHeight * 6;

  //  uint32_t* pIndex;
  //  result.Indices = BufferData(indexCount, pIndex);

  //  for (uint32_t j = 0; j < triangleHeight; j++)
  //  {
  //    for (uint32_t i = 0; i < triangleWidth; i++)
  //    {
  //      *pIndex++ = j * subdivisions.x + i;
  //      *pIndex++ = j * subdivisions.x + i + 1;
  //      *pIndex++ = (j + 1) * subdivisions.x + i;
  //      *pIndex++ = j * subdivisions.x + i + 1;
  //      *pIndex++ = (j + 1) * subdivisions.x + i + 1;
  //      *pIndex++ = (j + 1) * subdivisions.x + i;
  //    }
  //  }

  //  //Topology
  //  result.Topology = PrimitiveTopology::TriangleList;

  //  return result;
  //}
}