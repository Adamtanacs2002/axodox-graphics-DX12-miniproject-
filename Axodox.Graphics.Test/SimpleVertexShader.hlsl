cbuffer Constants : register(b0)
{
  float4x4 Transformation;
  int2 MeshletSize;
};

struct input_t
{
  uint Id : SV_VertexID;
  float3 Position : POSITION;
  float2 Texture : TEXCOORD;
};

struct output_t
{
  float4 Screen : SV_POSITION;
  float2 Texture : TEXCOORD;
};

output_t main(input_t input)
{
  output_t output;
  float size = 10.0f;
  input.Position.xy = float2((input.Id % MeshletSize.x) / size, (input.Id / MeshletSize.x) / size);
  output.Screen = mul(float4(input.Position.xyz, 1), Transformation);
  output.Texture = input.Texture;
  return output;
}