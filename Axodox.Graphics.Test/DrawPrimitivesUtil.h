#pragma once

#include "BinUtil.h"
#include <DirectXMath.h>

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b
#define SQPOW(a) a*a

using namespace BinUtilLib;

ImVec2 operator+(ImVec2 const a, ImVec2 const b)
{
	return ImVec2(a.x + b.x, a.y + b.y);
}

ImVec2 operator/(ImVec2 const a, float const d)
{
	return ImVec2(a.x / d, a.y / d);
}

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

uint32_t getParent(uint32_t id)
{
	return floor(id / 2.0f);
}

uint32_t getLeftChild(uint32_t id)
{
	return id*2;
}

uint32_t getRightChild(uint32_t id)
{
	return id * 2 + 1;
}

// Return a list of for IDs of neighbouring triangles.
std::array<int,4> GetNeighbours(uint32_t id)
{
	int n[4] = {0,0,0,1};
	uint32_t d = BinUtil::FindMSB(id);

	if (d <= 0)
		return std::array<int,4>({0,0,0,0});


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

	return std::to_array(n);
}

static XMMATRIX m0 = XMLoadFloat3x3(
	new  XMFLOAT3X3{ 0,	 0,	  1,
					0,	 1,	  0,
					0.5f,0.5f,0 });

static XMMATRIX m1 = XMLoadFloat3x3(
	new XMFLOAT3X3{ 1,	 0,	  0,
					0,	 0,	  1,
					0.5f,0.5f,0 });

static std::vector<ColoredTri> PopulateList(
	std::vector<uint32_t> ids, 
	ColoredTri base,
	ImColor col)
{
	std::vector<ColoredTri> triangles = {};

	XMMATRIX baseTri = XMMatrixTranspose(XMLoadFloat3x3(
		new  XMFLOAT3X3{ base.p0->x, base.p2->x, base.p1->x,
						 base.p0->y, base.p2->y, base.p1->y,
						 0,			  0,		   0 }));

	for (auto id : ids)
	{
		XMMATRIX m = XMMatrixIdentity();
		uint32_t d = BinUtil::FindMSB(id);

		for (int bitMask = d >> 1; bitMask > 0; bitMask = bitMask >> 1)
		{
			uint32_t b = (id & bitMask);

			m = b == 0 ? 
				XMMatrixMultiply(m0, m) :
				XMMatrixMultiply(m1, m);
		}

		XMMATRIX prod = XMMatrixTranspose(
			XMMatrixMultiply(m, baseTri)
		);

		ColoredTri res = {
			id,
			new ImVec2(prod.r->m128_f32[0],prod.r->m128_f32[4]),
			new ImVec2(prod.r->m128_f32[1],prod.r->m128_f32[5]),
			new ImVec2(prod.r->m128_f32[2],prod.r->m128_f32[6]),
			col
		};

		triangles.push_back(res);
		// TODO: multiply with matrices according to paper
		// EXAMPLE : 5 = 101
		// M_5 = M1 x M0
	}

	return triangles;
}

static void mergeBisectors(std::vector<uint32_t>& ids, uint32_t& in)
{
	auto parent = getParent(in);


	// TODO: Fix errors
	/* find leftChild -> delete leftChild if found
	 * find rightChild -> delete rightChild
	 * if not found : reverse leftChild deletion
	 */
	auto leftChild = std::find(
		ids.begin(), ids.end(), getLeftChild(parent));

	if (leftChild != ids.end()) 
	{
		uint32_t tmp = *leftChild;
		ids.erase(leftChild);

		auto rightChild = std::find(
			ids.begin(), ids.end(), getRightChild(parent));
		if (rightChild != ids.end())
		{
			ids.erase(rightChild);
			ids.push_back(parent);
		}
		else
		{
			ids.push_back(tmp);
		}
	}
}

static void divideBisector(std::vector<uint32_t>& ids,uint32_t& in)
{

	ids.erase(std::find(ids.begin(), ids.end(), in));

	in *= 2;
	ids.push_back(in);
	ids.push_back(in+1);
}

// Divide input tri into left and right tri
ColoredTri subdivide(ColoredTri& input, int& depth, ImColor col)
{
	depth++;

	// p0 : A; p1 : B; p2 : C
	float distA = sqrt(powf(input.p0->x - input.p1->x, 2) +
		powf(input.p0->y - input.p1->y, 2));
	float distB = sqrt(powf(input.p0->x - input.p2->x, 2) +
		powf(input.p0->y - input.p2->y, 2));
	float distC = sqrt(powf(input.p1->x - input.p2->x, 2) +
		powf(input.p1->y - input.p2->y, 2));

	float max = MAX(MAX(distA, distB), distC);

	uint32_t nID = input.id * 2;
	if (input.id % 2 == 0) nID++;

	// TODO: make it with matrix mult.
	/* V = [p0,p1,p2] (p2 derékszög)
	 * M = M0 v M1
	 * (_T = transzponált)
	 * V' = (M0*V_T)_T
	 */
	XMMATRIX tmp1 = XMMatrixTranspose(XMLoadFloat3x3(
	new  XMFLOAT3X3	{input.p0->x, input.p2->x, input.p1->x,
					 input.p0->y, input.p2->y, input.p1->y,
					 0,			  0,		   0 }));


	XMMATRIX left = XMMatrixTranspose(XMMatrixMultiply(m0, tmp1));
	XMMATRIX right = XMMatrixTranspose(XMMatrixMultiply(m1,tmp1));

	ImVec2 p3;

	input = {
		nID,
		new ImVec2(right.r->m128_f32[0],right.r->m128_f32[4]),
		new ImVec2(right.r->m128_f32[1],right.r->m128_f32[5]),
		new ImVec2(right.r->m128_f32[2],right.r->m128_f32[6]),
		input.col
	};

	ColoredTri outTri{
		nID + 1,
		new ImVec2(left.r->m128_f32[0],left.r->m128_f32[4]),
		new ImVec2(left.r->m128_f32[1],left.r->m128_f32[5]),
		new ImVec2(left.r->m128_f32[2],left.r->m128_f32[6]),
		col };

	return outTri;
}