#pragma once

#include "../ImGUI/imgui.h"

struct ColoredTri
{
	uint32_t id = 1;
	ImVec2* p0;
	ImVec2* p1;
	ImVec2* p2;
	ImColor col;
};

namespace DrawPrimitivesUtil
{
	ImVec2 operator+(ImVec2 const a, ImVec2 const b);
	ImVec2 operator/(ImVec2 const a, float const d);

	ColoredTri* getById(int id, std::vector<ColoredTri>& tris);

	std::array<int, 4> GetNeighbours(uint32_t id);

	std::vector<ColoredTri> PopulateList(std::vector<uint32_t> ids, ColoredTri base, ImColor col);

	void mergeBisectors(std::vector<uint32_t>& ids, uint32_t& in);
	void divideBisector(std::vector<uint32_t>& ids, uint32_t& in);
	ColoredTri subdivide(ColoredTri& input, int& depth, ImColor col);
}