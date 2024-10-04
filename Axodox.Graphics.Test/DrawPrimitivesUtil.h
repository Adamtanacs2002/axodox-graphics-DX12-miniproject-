#pragma once
#include "../ImGUI/imgui.h"

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
#define sqpow(a) a*a

struct Tri {
	ImVec2 p0;
	ImVec2 p1;
	ImVec2 p2;
};

struct ColoredTri
{
	int id = 1;
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

	//          o
	//			   /|\
	//		   /  |  \
	//		 /		|    \
	//	 /		  |      \
	//	o-------o-------o
	//         p3

	ImVec2 p3;
	ColoredTri out;
	if (max == distA)
	{
		p3 = { (input.p0 + input.p1) / 2.0f };
		out = ColoredTri{
			.id = input.id * 2,
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
			.id = input.id * 2,
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
			.id = input.id * 2,
			.p0 = input.p0,
			.p1 = p3,
			.p2 = input.p2,
			.col = col
		};
		input.p2 = p3;

	}

	input.id = input.id * 2 + 1;
	return out;
}