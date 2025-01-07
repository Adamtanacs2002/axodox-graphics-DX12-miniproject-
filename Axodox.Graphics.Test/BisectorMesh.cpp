#include "pch.h"
#include "BisectorMesh.h"

BisectorMesh BisectorMesh::CreateQuad(const ResourceAllocationContext& context)
{
	MeshDescription quad;
	{
		// TODO: Change back to Vertex type
		/* From Vertex Id only to
		 * Pos & Texel
		 */
		// Create Vertices and Indices

		float size = 1.0f;
		float texMax = 1.0f;

		quad.Vertices = {
			VertexPositionTexture{{0,0,0},PackedVector::XMUSHORTN2{0.0f,0.0f}},
			VertexPositionTexture{{size,0,0},PackedVector::XMUSHORTN2{texMax,0.0f}},
			VertexPositionTexture{{0,size,0},PackedVector::XMUSHORTN2{0.0f,texMax}},
			VertexPositionTexture{{size,size,0},PackedVector::XMUSHORTN2{texMax,texMax}},
		};

		quad.Indices = {
			0,1,2,
			2,1,3
		};

		quad.Topology = PrimitiveTopology::PatchList3;

	}

	BisectorMesh res = BisectorMesh(context, std::move(quad));
	res.Bisectors.push_back({index++,{0,1,2}});
	res.Bisectors.push_back({ index++,{1,3,2} });
	res.neighbours.push_back({0,1});

	return res;
}