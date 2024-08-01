#pragma once
namespace Miniproject
{

  #pragma region Mesh Data
  struct MeshletVertex
  {
    float attitude;
    // USHORT pitch;
    // USHORT yaw;
  };

  struct Meshlet
  {
    DirectX::XMFLOAT2 pos;
    MeshletVertex vertices[8][8];

    Meshlet CreateTestMeshlet(float x, float y /*float heights[64]*/)
    {
      Meshlet rt;
      rt.pos = { x, y };
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          MeshletVertex vtx;
          vtx.attitude = 1.f;// ((i % 2) * 0.1f) + ((j % 2) * 0.1f);
          rt.vertices[i][j] = vtx;
        }
      }

      return rt;
    }

    Meshlet CreateTestMeshlet(float x, float y, float* heights)
    {
      Meshlet rt;
      rt.pos = { x, y };
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          MeshletVertex vtx;
          vtx.attitude = heights[(i * 8) + j] - 4.f;
          rt.vertices[i][j] = vtx;
        }
      }

      return rt;
    }

    Meshlet()
    {
      pos = { 0.0f,0.0f };
    }

    Meshlet(DirectX::XMFLOAT3* vertexes)
    {
      float allX = 0.f, allY = 0.f;
      for (int i = 0; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          MeshletVertex vtx;
          allX += vertexes->x;
          allY += vertexes->y;
          vtx.attitude = vertexes[(i * 8) + j].z;
          vertices[i][j] = vtx;
        }
      }

      pos = { allX / 8.0f, allY / 8.0f };
    }
  };
  #pragma endregion

	/// <summary>
	/// Class for reading height data from files.
	/// </summary>
	class HeightmapReader
	{
	private:
		/// <summary>
		/// Path to the file that contains the height data.
		/// </summary>
		std::filesystem::path _path;
		/// <summary>
		/// Inner vector that contains all heights by row.
		/// </summary>
		std::vector< std::vector<float>> _heights;
		void GetMeshletHeigthsFromTo(int fromx, int tox, int fromy, int toy, float* arr);
	public:
		/// <summary>
		/// Basic constructor that takes in the path to the heightmap
		/// </summary>
		/// <param name="path">Path towards the file containing the height data</param>
		HeightmapReader(std::filesystem::path);
		/// <summary>
		/// Reads data that is contained inside the file at _path path.
		/// </summary>
		std::vector<std::vector<float>> GetHeights();
		void ReadHeightmapText();
		void GetMeshletHeigths(int x, int y, float* arr);
	};
}

