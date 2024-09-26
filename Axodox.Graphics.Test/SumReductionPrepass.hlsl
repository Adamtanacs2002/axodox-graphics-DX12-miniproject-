// requires cbt.glsl
#define CBT_FLAG_WRITE
#include "ConcurrentBinaryTree.hlsl"

#ifndef CBT_LOCAL_SIZE_X
#   define CBT_LOCAL_SIZE_X 256
#endif

int u_CbtID = 0;
int u_PassID;

[numthreads(1, 1, 1)]
void main(uint3 index : SV_DispatchThreadID)
{
  const int cbtID = u_CbtID;
  uint cnt = (1u << u_PassID);
  uint threadID = index.x;

  if (threadID < cnt)
  {
    uint nodeID = threadID + cnt;
    uint alignedBitOffset = cbt__NodeBitID(cbt_CreateNode(nodeID, u_PassID));
    uint bitField = cbt_HeapRead(alignedBitOffset >> 5u);
    uint bitData = 0u;

        // 2-bits
    bitField = (bitField & 0x55555555u) + ((bitField >> 1u) & 0x55555555u);
    bitData = bitField;
    cbt__HeapWrite((alignedBitOffset - cnt) >> 5u, bitData);

        // 3-bits
    bitField = (bitField & 0x33333333u) + ((bitField >> 2u) & 0x33333333u);
    bitData = ((bitField >> 0u) & (7u << 0u))
                | ((bitField >> 1u) & (7u << 3u))
                | ((bitField >> 2u) & (7u << 6u))
                | ((bitField >> 3u) & (7u << 9u))
                | ((bitField >> 4u) & (7u << 12u))
                | ((bitField >> 5u) & (7u << 15u))
                | ((bitField >> 6u) & (7u << 18u))
                | ((bitField >> 7u) & (7u << 21u));
    cbt__HeapWriteExplicit(cbt_CreateNode(nodeID >> 2u, u_PassID - 2), 24, bitData);

        // 4-bits
    bitField = (bitField & 0x0F0F0F0Fu) + ((bitField >> 4u) & 0x0F0F0F0Fu);
    bitData = ((bitField >> 0u) & (15u << 0u))
                | ((bitField >> 4u) & (15u << 4u))
                | ((bitField >> 8u) & (15u << 8u))
                | ((bitField >> 12u) & (15u << 12u));
    cbt__HeapWriteExplicit(cbt_CreateNode(nodeID >> 3u, u_PassID - 3), 16, bitData);

        // 5-bits
    bitField = (bitField & 0x00FF00FFu) + ((bitField >> 8u) & 0x00FF00FFu);
    bitData = ((bitField >> 0u) & (31u << 0u))
                | ((bitField >> 11u) & (31u << 5u));
    cbt__HeapWriteExplicit(cbt_CreateNode(nodeID >> 4u, u_PassID - 4), 10, bitData);

        // 6-bits
    bitField = (bitField & 0x0000FFFFu) + ((bitField >> 16u) & 0x0000FFFFu);
    bitData = bitField;
    cbt__HeapWriteExplicit(cbt_CreateNode(nodeID >> 5u, u_PassID - 5), 6, bitData);
  }
}