#pragma once
#include "MutableMeshBase.h"

using namespace DirectX;

static uint32_t index = 0;

struct BisectorNeighbours
{
	uint32_t IdA, IdB;
};

struct Bisector
{
	uint32_t Id;
	uint32_t indices[3];
};

class BisectorMesh : MutableMeshBase
{
public:
	static BisectorMesh CreateQuad(const ResourceAllocationContext& context);

	BisectorMesh(const ResourceAllocationContext& context, MeshDescription&& description) :
	MutableMeshBase(context,std::move(description))
	{
	}

	void Draw(CommandAllocator& allocator, uint32_t instanceCount = 1)
	{
		DrawBase(allocator, instanceCount);
	}

	std::vector<BisectorNeighbours> neighbours = {};
	std::vector<Bisector> Bisectors = {};
};