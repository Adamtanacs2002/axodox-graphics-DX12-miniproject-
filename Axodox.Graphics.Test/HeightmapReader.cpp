#include "pch.h"
#include <fstream>
#include "HeightmapReader.h"

namespace Miniproject
{
	HeightmapReader::HeightmapReader(std::filesystem::path path) :
		_path(path)
	{

	}
	std::vector<std::vector<float>> HeightmapReader::GetHeights()
	{
		return _heights;
	}

	void HeightmapReader::ReadHeightmapText()
	{
		std::string StringData;
		std::string delimiter = "|";
		std::ifstream file(_path);
		size_t pos = 0;

		while (std::getline(file, StringData))
		{
			std::vector<float> row;
			std::string token;
			while ((pos = StringData.find(delimiter)) != std::string::npos)
			{
				token = StringData.substr(0, pos);
				row.push_back(std::stof(token));
				StringData.erase(0, pos + delimiter.length());
			}
			_heights.push_back(row);
		}
	}
	void HeightmapReader::GetMeshletHeigths(int x, int y, float* arr)
	{
		GetMeshletHeigthsFromTo(x * 8, (x + 1) * 8, y * 8, (y + 1) * 8, arr);
	}

	void HeightmapReader::GetMeshletHeigthsFromTo(int fromx, int tox, int fromy, int toy, float* arr)
	{
		int ii, jj;

		ii = 0;
		for (int i = fromx; i < tox; i++)
		{
			jj = 0;
			for (int j = fromy; j < toy; j++)
			{
				arr[(ii * 8) + jj] = (_heights.at(i).at(j));
				jj++;
			}
			ii++;
		}
	}
}