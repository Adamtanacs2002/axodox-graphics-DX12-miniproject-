#include "CBTCommon.hlsl"

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    MergeNode(2);
}