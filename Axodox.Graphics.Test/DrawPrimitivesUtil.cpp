#include "pch.h"

#include "DrawPrimitivesUtil.h"

#include "CbtCPU.h"
#include <DirectXMath.h>

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b
#define SQPOW(a) a*a

using namespace DirectX;

ImVec2 DrawPrimitivesUtil::operator+(ImVec2 const a, ImVec2 const b)
{
	return ImVec2(a.x + b.x, a.y + b.y);
}

ImVec2 DrawPrimitivesUtil::operator/(ImVec2 const a, float const d)
{
	return ImVec2(a.x / d, a.y / d);
}

ColoredTri* DrawPrimitivesUtil::getById(int id, std::vector<ColoredTri>& tris)
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

// Return a list of for IDs of neighbouring triangles.
std::array<int, 4> DrawPrimitivesUtil::GetNeighbours(uint32_t id)
{
	int n[4] = { 0,0,0,1 };
	uint32_t d = BinUtils::FindMSB(id) >> 1;

	if (id == 2)
		return { 0,0,3,2 };
	if (id == 3)
		return { 0,0,2,3 };

	for (int bitMask = d; bitMask > 0; bitMask = bitMask >> 1)
	{
		uint32_t b = (id & bitMask);

		// G0
		int tmp[4] = { n[0],n[1],n[2],n[3] };
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
		for (int i = 0; i < 4; i++)
		{
			n[i] = std::move(tmp[i]);
		}
	}

	return std::to_array(n);
}

static XMMATRIX m0 = XMLoadFloat3x3(
	new XMFLOAT3X3{ 1,	 0,	  0,
					0,	 0,	  1,
					0.5f,0.5f,0 });

static XMMATRIX m1 = XMLoadFloat3x3(
	new  XMFLOAT3X3{ 0,	 0,	  1,
					0,	 1,	  0,
					0.5f,0.5f,0 });

std::vector<ColoredTri> DrawPrimitivesUtil::PopulateList(
	std::vector<uint32_t> ids,
	ColoredTri base,
	ImColor col)
{
	// TODO: try to make it populate a VertexBuffer, then draw triangles between them
	/* IDEA: try to create vertex, if it already exists, don't
	 * Vertex IDs are consistent, vertex at 90 degrees angle (see demo coloring blue point)
	 */

	std::vector<ColoredTri> triangles = {};

	XMMATRIX baseTri = XMMatrixTranspose(XMLoadFloat3x3(
		new  XMFLOAT3X3{ base.p0->x, base.p2->x, base.p1->x,
						 base.p0->y, base.p2->y, base.p1->y,
						 0,			  0,		   0 }));

	for (auto id : ids)
	{
		XMMATRIX m = XMMatrixIdentity();
		uint32_t d = BinUtils::FindMSB(id);

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
	}

	return triangles;
}

static uint32_t GetParent(uint32_t id) { return floor<uint32_t>( id / 2); }
static uint32_t GetLeftChild(uint32_t id) { return id * 2; }
static uint32_t GetRightChild(uint32_t id) { return id * 2 + 1; }

void DrawPrimitivesUtil::mergeBisectors(std::vector<uint32_t>& ids, uint32_t& in)
{
	auto parent = GetParent(in);

	auto leftChild = std::find(
		ids.begin(), ids.end(), GetLeftChild(parent));

	// TODO: Propagate merging if leftChild == ids.end
	/* Try to get parent's Twin, if it doesn't exist, merge its children
	 * Check if MSB to decide to merge or not.
	 *
	 */
	if (leftChild != ids.end())
	{
		uint32_t tmp = *leftChild;
		ids.erase(leftChild);

		auto rightChild = std::find(
			ids.begin(), ids.end(), GetRightChild(parent));
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

void DrawPrimitivesUtil::divideBisector(std::vector<uint32_t>& ids, uint32_t& in)
{

	ids.erase(std::find(ids.begin(), ids.end(), in));

	// TODO: Propagate division to make correct bisectors
	/* Try to get Twin, if it fails, divide parent
	 * Problem : Neighbour algorithm returns incorrect twin sometimes
	 *
	 */

	in *= 2;
	ids.push_back(in);
	ids.push_back(in + 1);
}

// Divide input tri into left and right tri
ColoredTri DrawPrimitivesUtil::subdivide(ColoredTri& input, int& depth, ImColor col)
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


	XMMATRIX tmp1 = XMMatrixTranspose(XMLoadFloat3x3(
		new  XMFLOAT3X3{ input.p0->x, input.p2->x, input.p1->x,
						 input.p0->y, input.p2->y, input.p1->y,
						 0,			  0,		   0 }));


	XMMATRIX left = XMMatrixTranspose(XMMatrixMultiply(m0, tmp1));
	XMMATRIX right = XMMatrixTranspose(XMMatrixMultiply(m1, tmp1));

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