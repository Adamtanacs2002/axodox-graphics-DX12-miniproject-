Texture2D _texture : register(t0);
SamplerState _sampler : register(s0);

cbuffer Constants : register(b0)
{
  float4x4 Transformation;
  int2 MeshletSize;
  float MapSize;
  float MaxHeight;
};

struct input_t
{
  uint Id : SV_VertexID;
  // float3 Position : POSITION;
};

struct output_t
{
  float3 Coords : WORLDPOS;
  //float4 Screen : SV_Position;
  float2 Texture : TEXCOORD;
};

output_t main(input_t input)
{
  float3 PositionData = float3(1, 1, 1);
  output_t output;
  float2 calcTex = float2((
    input.Id % MeshletSize.x) / float(MeshletSize.x - 1),
    (input.Id / MeshletSize.x) % MeshletSize.y / float(MeshletSize.y - 1));
  PositionData.xy =
  float2(
    (input.Id % MeshletSize.x) * (MapSize / 100.0f),
    (input.Id / MeshletSize.x) * (MapSize / 100.0f));
  output.Coords = float3(PositionData.xy, 0);
  // mul(float4(PositionData.xy, PositionData.z * 6 * _texture.SampleLevel(_sampler, calcTex, 0).x, 1), Transformation);
  output.Texture = calcTex;
  return output;
}