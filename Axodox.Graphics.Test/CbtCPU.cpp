#include "pch.h"
#include "CbtCPU.h"

#include "DrawPrimitivesUtil.h"


using namespace BinUtils;

int BinUtils::FindMSB(uint32_t n)
{
	n |= n >> 1; // 100010001 | 010000100 = 110011001
	n |= n >> 2; // 110011001 | 001100110 = 111111111
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;

	// if MSB is not the final bit
	n = ((n + 1) >> 1)
	// if MSB is the final bit
	| (n & (1 << ((sizeof(n) * CHAR_BIT) - 1)));
	return n;
}

// Finds the index (from the right) of the MSB
// Note this is also the depth of the node.
int BinUtils::FindMSBIndex(int n)
{
	return log2(FindMSB(n));
}

int BinUtils::findBitFieldID(int bitID)
{
	return bitID / (sizeof(uint32_t) * CHAR_BIT) + 1;
}

// Returns BitID for a given node
int CbtCPU::EncodeNode(int nodeID) const
{
	return nodeID * pow(2, (depth) - BinUtils::FindMSBIndex(nodeID))
	- pow(2,depth);
}

int BinUtils::BinNodeDepth(int nodeID) { return BinUtils::FindMSBIndex(nodeID); }
// Returns ID of left child node
int BinUtils::NodeLeftChild(int nodeID) { return nodeID * 2; }
// Returns ID of right child node
int BinUtils::NodeRightChild(int nodeID) { return nodeID * 2 + 1; }
int BinUtils::NodeLeftSibling(int nodeID) { throw new std::exception("Not implemented yet."); }
int BinUtils::NodeRightSibling(int nodeID) { return nodeID | 0x1; }
// Returns ID of parent node
int BinUtils::NodeParent(int nodeID) { return nodeID / 2; }


// Counts the number of zeros after a bit.
int CbtCPU::CountZeros(int bitID)
{
	// TODO: make a more efficient counting function.
	int bitCount = pow(2, depth) - 1;

	uint32_t bitInd = bitID % BITFIELD_SIZE;
	uint32_t cnt = 0;
	bool v = ReadBinField(++bitID);
	while (bitCount > 0 && !v &&
		bitID < pwrtwo(depth))
	{
		cnt = cnt + !v;
		bitCount--;
		v = ReadBinField(++bitID);
	}

	return cnt;
}

// Return NodeID for a given bit.
int CbtCPU::DecodeNode(int bitID)
{
	int cnt = CountZeros(bitID);

	auto aa = depth - log2(1 + cnt);
	int A = pow(2,depth) + bitID;

	int l[1024];

	bool NeedCorrection = false;
	int correction = 0;
	for (int i = 0; i < depth + 1; i++)
	{
		if (NeedCorrection) correction++;
		l[depth - i] = A;
		if (A % 2 == 1) NeedCorrection = true;
		A = A / 2;
	}

	return l[(int)aa];
}

vector<uint32_t> CbtCPU::PopulateListCbt()
{
	std::vector<uint32_t> res = {};

	for (int i = 0; i < pow(2,depth);i++)
	{
		if (ReadBinField(i))
		{
			res.push_back(DecodeNode(i));
		}
	}

	return res;
}

void CbtCPU::WriteBinField(int bitID, bool value)
{
	uint32_t bitMask = 0x80000000;
	bitMask = ~(bitMask >> bitID);
	uint32_t bitData = ~bitMask * uint32_t(value);

	binField[BinUtils::findBitFieldID(bitID)] &= bitMask;
	binField[BinUtils::findBitFieldID(bitID)] |= bitData;
}

// Returns boolean based on value
// HLSL
// non zero -> true
// zero -> false
bool CbtCPU::ReadBinField(int bitID)
{
	uint32_t bitMask = 0x80000000;
	bitMask = bitMask >> bitID;

	bitMask &= binField[BinUtils::findBitFieldID(bitID)];
	
	bool tmp = bool(bitMask);
	return tmp;
}

CbtCPU::CbtCPU()
{
	depth = DEPTH;

	Reset();
}

void CbtCPU::Reset()
{
	binField[1] = 0x80000000;

	for (int i = 2; i < sizeof(binField) / sizeof(binField[0]); i++)
	{
		binField[i] = 0x00000000;
	}
}

bool CbtCPU::IsLeafNode(uint32_t nodeID)
{
	if (nodeID == 0) return false;
	return ReadBinField(EncodeNode(nodeID)) == 1;
}

// Get true neighbours of a bisector.
std::array<int, 4> CbtCPU::GetTrueNeighbour(uint32_t nodeID)
{
	auto n = DrawPrimitivesUtil::GetNeighbours(nodeID);

	if (!IsLeafNode(n[2]))
	{
		n[2] = n[2] / 2;
	}

	if (!IsLeafNode(n[0]))
	{
		n[0] = n[0] * 2;
	}

	if (!IsLeafNode(n[1]))
	{
		n[1] = n[1] * 2 + 1;
	}

	return n;
}

// Split a node into to two child nodes. Creates conforming LEB mesh.
void CbtCPU::ConformingSplit(int nodeID)
{
	SplitNode(nodeID);
	nodeID = DrawPrimitivesUtil::GetNeighbours(nodeID)[2];
	while (nodeID > 1)
	{
		SplitNode(nodeID);
		nodeID = nodeID / 2;
		SplitNode(nodeID);
		nodeID = DrawPrimitivesUtil::GetNeighbours(nodeID)[2];
	}
}

// Split a node into to two child nodes.
void CbtCPU::SplitNode(int nodeID)
{
	if (FindMSBIndex(nodeID) >= depth) return;
	nodeID = nodeID * 2 + 1;

	WriteBinField(EncodeNode(nodeID), 1);
}

// Merge a node with its sibling node. Creates conforming LEB mesh.
void CbtCPU::ConformingMerge(int nodeID)
{
	if (nodeID == 1) return;

	int siblingID = nodeID ^ 0x1;
	array<int, 4>diamondID = DrawPrimitivesUtil::GetNeighbours(nodeID/2);

	int leftID = diamondID[2] * 2;
	int rightID = diamondID[2] * 2 + 1;

	if (IsLeafNode(siblingID))
	{
		// TODO: Fix merging problem.
		MergeNode(nodeID);
	}

	auto dr = FindMSBIndex(rightID);
	auto dn = FindMSBIndex(nodeID);

	if (IsLeafNode(leftID) &&
		IsLeafNode(rightID) &&
		dr == dn)
	{
		MergeNode(rightID);
	}
}

// Merge a node with its sibling node.
void CbtCPU::MergeNode(int nodeID)
{
	nodeID = nodeID | 0x1;
	WriteBinField(EncodeNode(nodeID), false);
}

std::string CbtCPU::DisplayBinField()
{
	std::string output_str = "";
	//output_str += 
	//	"Depth: " + std::to_string(binField[0]) + 
	//	"\nBitField : ";
	for (int i = 1; i < sizeof(binField) / sizeof(uint32_t); i++)
	{
		auto temp = binField[i];
		std::bitset<sizeof(binField[0]) * CHAR_BIT> temp_bits(temp);
		output_str += temp_bits.to_string();
		if (i < (sizeof(binField) / sizeof(uint32_t)) - 1)
			output_str += "|";
	}
	return output_str;
}
