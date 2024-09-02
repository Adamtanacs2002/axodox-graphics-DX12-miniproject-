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
  float3 Position : POSITION;
};

struct output_t
{
  float4 Screen : WORLDPOS;
  //float4 Screen : SV_Position;
  float2 Texture : TEXCOORD;
};

output_t main(input_t input)
{
  output_t output;
  float2 calcTex = float2((
    input.Id % MeshletSize.x) / float(MeshletSize.x - 1),
    (input.Id / MeshletSize.x) % MeshletSize.y / float(MeshletSize.y - 1));
  input.Position.xy = 
  float2(
    (input.Id % MeshletSize.x) * (MapSize / 100.0f),
    (input.Id / MeshletSize.x) * (MapSize / 100.0f));
  output.Screen = mul(float4(input.Position.xy, input.Position.z * MaxHeight, 1), Transformation);
  output.Texture = calcTex;
  return output;
}