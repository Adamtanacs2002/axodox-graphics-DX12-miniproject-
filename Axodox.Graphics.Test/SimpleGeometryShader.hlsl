cbuffer Constants : register(b0)
{
    float4x4 Transformation;
};


struct DS_OUTPUT
{
    float3 pos : WORLDPOS;
    float2 tex : TEXCOORD;
};

struct GS_OUTPUT
{
    float4 Screen : SV_POSITION;
    float2 Texture : TEXCOORD;
};

// Creates a new triangle along the LE using LEB.
void CreateTri(inout DS_OUTPUT o_tri[3], out DS_OUTPUT n_tri[3])
{
    n_tri[0].pos = o_tri[0].pos;
    n_tri[0].tex = n_tri[0].tex;
    n_tri[1].pos = o_tri[1].pos;
    n_tri[1].tex = n_tri[1].tex;

    DS_OUTPUT leb;
    leb.pos = (o_tri[1].pos - o_tri[2].pos) / 2.0f;
    leb.tex = (o_tri[1].tex - o_tri[2].tex) / 2.0f;

    n_tri[2].pos = leb.pos;
    n_tri[2].tex = leb.tex;
    o_tri[2].pos = leb.pos;
    o_tri[2].tex = leb.tex;
}

[maxvertexcount(36)]
void main(
	triangle DS_OUTPUT input[3], 
	inout TriangleStream<GS_OUTPUT> output
)
{
	for (uint i = 0; i < 3; i++)
    {
		GS_OUTPUT element;

        element.Screen = mul(float4(input[i].pos.xyz, 1), Transformation);
        element.Texture = input[i].tex;
        output.Append(element);
    }
}