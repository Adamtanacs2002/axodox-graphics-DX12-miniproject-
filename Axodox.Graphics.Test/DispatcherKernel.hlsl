#include "CBTCommon.hlsl"

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    cbt_bitfields[0] = 6;
    for (int i = 1; i < 3; i++)
    {
        cbt_bitfields[i] = 0;
    }
	WriteBinField(0, true);
}