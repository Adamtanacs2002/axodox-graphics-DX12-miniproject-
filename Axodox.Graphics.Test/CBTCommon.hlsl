
// 0 - depth of binary tree
// 1.. - node data
RWStructuredBuffer<uint> cbt_bitfields : register(u1); // writeable
// StructuredBuffer<uint> uavTest : register(u1) // read-only

#define CHAR_BIT 8
#define UINT_SIZE 4

uint FindMSB(uint n);
uint FindMSBIndex(uint n);
uint FindBitFieldID(uint bitID);
uint CbtMaxDepth();
uint EncodeNode(uint nodeID);
void WriteBinField(uint bitID, bool value);
bool ReadBinField(uint bitID);
void SplitNode(uint nodeID);
void MergeNode(uint nodeID);

// Callbacks

// ---------

uint FindMSB(uint n)
{
    n |= n >> 1; // 100010001 | 010000100 = 110011001
    n |= n >> 2; // 110011001 | 001100110 = 111111111
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

	// if MSB is not the final bit
    n = ((n + 1) >> 1)
	// if MSB is the final bit
	| (n & (1 << ((UINT_SIZE * CHAR_BIT) - 1)));
    return n;
}

uint FindMSBIndex(uint n)
{
    return log2(FindMSB(n));
}

uint FindBitFieldID(uint bitID)
{
    return bitID / (UINT_SIZE * CHAR_BIT) + 1;
}

uint CbtMaxDepth()
{
    return cbt_bitfields[0];
}

uint EncodeNode(uint nodeID)
{
    return nodeID * pow(2, CbtMaxDepth() - FindMSBIndex(nodeID))
	- pow(2, CbtMaxDepth());
}

// Not implemented yet
uint DecodeNode(uint bitID) { return 0; }
uint NodeLeftSibling(uint bitID) { return 0; }
uint NodeRightSibling(uint bitID) { return 0; }
// -------------------

uint NodeDepth(uint nodeID) { return FindMSBIndex(nodeID); }
uint NodeLeftChild(uint nodeID) { return nodeID*2; }
uint NodeRightChild(uint nodeID) { return nodeID*2 + 1; }
uint NodeParent(uint nodeID) { return nodeID / 2; }

void WriteBinField(uint bitID, bool value)
{
    uint bitMask = 0x80000000;
    bitMask = ~(bitMask >> bitID);
    uint bitData = ~bitMask * uint(value);

    cbt_bitfields[FindBitFieldID(bitID)] &= bitMask;
    cbt_bitfields[FindBitFieldID(bitID)] |= bitData;
}

bool ReadBinField(uint bitID)
{
    uint bitMask = 0x80000000;
    bitMask = bitMask >> bitID;

    bitMask &= cbt_bitfields[FindBitFieldID(bitID)];
	
    bool tmp = bool(bitMask);
    return tmp;
}

void SplitNode(uint nodeID)
{
	uint tmpBitID = EncodeNode(NodeRightChild(nodeID));
	
	if (ReadBinField(EncodeNode(nodeID)))
	{
	// Left child already set

	// Right child
		WriteBinField(tmpBitID, true);
	}
}

void MergeNode(uint nodeID)
{
    if (nodeID != 1)
    {
        int parentID = NodeParent(nodeID);

        if (EncodeNode(parentID) == EncodeNode(nodeID))
        {
            WriteBinField(EncodeNode(NodeRightChild(parentID)), false);
        }
        else
        {
            WriteBinField(EncodeNode(nodeID), false);
        }
    }
}