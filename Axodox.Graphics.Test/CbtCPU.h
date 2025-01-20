#pragma once

#include <bitset>
#include <cstdint>
#include <string>

#define DEPTH 7
#define BITFIELD_SIZE 32
template <class T>
constexpr T pwrtwo(T exponent) {
	return (T(1) << exponent);
}

namespace BinUtils
{
	int FindMSB(uint32_t n);
	int FindMSBIndex(int n);
	int findBitFieldID(int bitID);
	int BinNodeDepth(int nodeID);
	int NodeLeftChild(int nodeID);
	int NodeRightChild(int nodeID);
	int NodeLeftSibling(int nodeID);
	int NodeRightSibling(int nodeID);
	int NodeParent(int nodeID);
};

class CbtCPU
{
private:
	int CountZeros(int bitID);
	int EncodeNode(int nodeID) const;
	int DecodeNode(int bitID);
	void WriteBinField(int bitID, bool value);
	bool ReadBinField(int bitID);
	bool IsLeafNode(uint32_t nodeID);
public:
	std::array<int, 4> GetTrueNeighbour(uint32_t nodeID);


	uint32_t binField[1 + pwrtwo(DEPTH) / BITFIELD_SIZE];
	uint32_t depth = binField[0];
	CbtCPU();

	void Reset();
	int BitFieldHeapID(int nodeID);

	void ConformingSplit(int nodeID);
	void SplitNode(int nodeID);
	void ConformingMerge(int nodeID);
	void MergeNode(int nodeID);

	std::string DisplayBinField();

	vector<uint32_t> PopulateListCbt();
};

