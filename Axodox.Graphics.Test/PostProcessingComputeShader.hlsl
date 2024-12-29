#include "CBTCommon.hlsl"

Texture2D _input : register(t0);
RWTexture2D<unorm float4> _output : register(u0);
SamplerState _sampler : register(s0);

cbuffer Constants : register(b0)
{
  float Time;
}

[numthreads(16, 16, 1)]
void main(uint3 index : SV_DispatchThreadID )
{

}