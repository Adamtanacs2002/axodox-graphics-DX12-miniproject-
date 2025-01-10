#pragma once
#include "../ImGUI/imgui.h"
#include "BinUtil.h"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
#define sqpow(a) a*a

using namespace BinUtilLib;

struct ColoredTri
{
	uint32_t id = 1;
	ImVec2 p0;
	ImVec2 p1;
	ImVec2 p2;
	ImColor col;
};

ImVec2 operator+(ImVec2 const a, ImVec2 const b)
{
	return ImVec2(a.x + b.x, a.y + b.y);
}

ImVec2 operator/(ImVec2 const a, float const d)
{
	return ImVec2(a.x / d, a.y / d);
}

static ImColor depthColor[5] = {
	ImColor(ImVec4(0.970f, 0.0582f, 0.058f, 1.0f)),
	ImColor(ImVec4(0.104f, 0.0582f, 0.970f, 1.0f)),
	ImColor(ImVec4(0.304f, 0.2582f, 0.670f, 1.0f)),
	ImColor(ImVec4(0.904f, 0.6582f, 0.670f, 1.0f)),
	ImColor(ImVec4(0.104f, 0.9270f, 0.058f, 1.0f))
};

static int depth = 0;

ColoredTri* getById(int id, std::vector<ColoredTri>& tris)
{
	ColoredTri* res = nullptr;
	for (int i = 0; i < tris.size(); i++)
	{
		if (tris[i].id == id)
		{
			res = &tris[i];
		}
	}
	return res;
}

ColoredTri* getParent(uint32_t id, std::vector<ColoredTri>& tris)
{
	return getById(floor(id / 2.0f),tris);
}

ColoredTri* getLeftChild(uint32_t id, std::vector<ColoredTri>& tris)
{
	return getById(id*2, tris);
}

ColoredTri* getRightChild(uint32_t id, std::vector<ColoredTri>& tris)
{
	return getById(id * 2 + 1, tris);
}

ColoredTri* GetNeighbours(uint32_t id, std::vector<ColoredTri>& tris)
{
	int n[4] = {0,0,0,1};
	uint32_t d = BinUtil::FindMSB(id);

	if (d <= 0)
		return nullptr;

	for (int bitMask = d >> 1; bitMask > 0; bitMask = bitMask >> 1)
	{
		uint32_t b = (id & bitMask);

		// G0
		int tmp[4] = {n[0],n[1],n[2],n[3]};
		if (b == 0)
		{
			tmp[0] = 2 * n[3] + 1;
			tmp[1] = 2 * n[2] + 1;
			tmp[2] = 2 * n[1] + 1;
			tmp[3] = 2 * n[3];
		}
		// G1
		else
		{
			tmp[0] = 2 * n[2];
			tmp[1] = 2 * n[3];
			tmp[2] = 2 * n[0];
			tmp[3] = 2 * n[3] + 1;
		}
		for (int i = 0; i < 4; i++) n[i] = std::move(tmp[i]);
	}

	return nullptr;
}

// Divide input tri into left and right tri
ColoredTri subdivide(ColoredTri& input)
{
	ImColor col = depthColor[depth % 5];
	depth++;

	// p0 : A; p1 : B; p2 : C
	float distA = sqrt(powf(input.p0.x - input.p1.x,2) + 
		powf(input.p0.y - input.p1.y, 2));
	float distB = sqrt(powf(input.p0.x - input.p2.x, 2) +
		powf(input.p0.y - input.p2.y, 2));
	float distC = sqrt(powf(input.p1.x - input.p2.x, 2) +
		powf(input.p1.y - input.p2.y, 2));

	float max = max(max(distA, distB), distC);

	uint32_t nID = input.id * 2;
	if (input.id % 2 == 0) nID++;

	ImVec2 p3;
	ColoredTri out;
	if (max == distA)
	{
		p3 = { (input.p0 + input.p1) / 2.0f };
		out = ColoredTri{
			.id = nID,
			.p0 = p3,
			.p1 = input.p1,
			.p2 = input.p2,
			.col = col
		};

		input.p1 = p3;
	}
	if (max == distB)
	{
		p3 = { (input.p0 + input.p2) / 2.0f };
		out = ColoredTri{
			.id = nID,
			.p0 = input.p0,
			.p1 = input.p1,
			.p2 = p3,
			.col = col
		};

		input.p0 = p3;
	}
	if (max == distC)
	{
		p3 = { (input.p1 + input.p2) / 2.0f };
		out = ColoredTri{
			.id = nID,
			.p0 = input.p0,
			.p1 = p3,
			.p2 = input.p2,
			.col = col
		};
		input.p2 = p3;

	}

	if (input.id % 2 == 0) input.id = --nID;
	else input.id = ++nID;

	return out;
}