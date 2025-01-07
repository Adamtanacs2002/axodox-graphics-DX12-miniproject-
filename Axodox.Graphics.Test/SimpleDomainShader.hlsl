Texture2D _texture : register(t0);
SamplerState _sampler : register(s0);

cbuffer Constants : register(b0)
{
	float4x4 Transformation;
    float MaxHeight;
    float tessFact;
};

struct DS_OUTPUT
{
	float4 vPosition: SV_POSITION;
	float2 tex : TEXCOORD;
};

struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : WORLDPOS;
	float2 Texture : TEXCOORD;
};

struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor;
	float InsideTessFactor			: SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT Output;

    Output.vPosition.xy = (patch[0].vPosition * domain.x + patch[1].vPosition * domain.y + patch[2].vPosition * domain.z).xy;

	Output.tex = patch[0].Texture * domain.x + patch[1].Texture * domain.y + patch[2].Texture * domain.z;

    Output.vPosition.z = 10 * _texture.SampleLevel(_sampler, Output.tex, 0).x;

	Output.vPosition = mul(float4(Output.vPosition.xyz,1), Transformation);


	return Output;
}
