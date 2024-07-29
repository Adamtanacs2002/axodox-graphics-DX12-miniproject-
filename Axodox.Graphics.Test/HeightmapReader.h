#pragma once
namespace Miniproject
{
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
		void ReadHeightmap();
		void GetMeshletHeigths(int x, int y, float* arr);
	};
}

