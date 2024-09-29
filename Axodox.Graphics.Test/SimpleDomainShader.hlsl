struct DS_OUTPUT
{
	float4 vPosition: SV_POSITION;
  float2 tex : TEXCOORD;
};

struct HS_CONTROL_POINT_OUTPUT
{
	float4 vPosition : WORLDPOS;
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

	Output.vPosition = float4(
		patch[0].vPosition*domain.x+patch[1].vPosition*domain.y+patch[2].vPosition*domain.z);
	
 // Output.vPosition.y = _texture.SampleLevel(_sampler,
	//patch[0].vPosition.xz * domain.x + patch[1].vPosition.xz * domain.y + patch[2].vPosition.xz * domain.z,
	//0);
	
  Output.tex = patch[0].Texture;

	return Output;
}
