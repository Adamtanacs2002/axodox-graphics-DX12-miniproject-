Texture2D _texture : register(t0);
SamplerState _sampler : register(s0);

cbuffer Constants : register(b0)
{
  float4x4 Transformation;
  int2 MeshletSize;
  float MapSize;
  float MaxHeight;
};

// VertexID
//struct input_t
//{
//  uint Id : SV_VertexID;
//  // float3 Position : POSITION;
//};

struct input_t
{
    float3 Position : POSITION;
    float2 Texture : TEXCOORD;
};

struct output_t
{
  float3 Coords : WORLDPOS;
  //float4 Screen : SV_Position;
  float2 Texture : TEXCOORD;
};

output_t main(input_t input)
{
	output_t output;

	// Transfer data
	output.Coords = float3(input.Position.xy * MapSize,0);
	output.Texture = input.Position;

	return output;
}