// Input control point
struct VS_CONTROL_POINT_OUTPUT
{
    float4 vPosition : WORLDPOS;
    float2 vUV : TEXCOORD0;
};

// Output control point
struct BEZIER_CONTROL_POINT
{
    float4 vPosition : WORLDPOS;
    float2 vUV : TEXCOORD0;
};

// Output patch constant data.
struct HS_CONSTANT_DATA_OUTPUT
{
    float Edges[3] : SV_TessFactor;
    float Inside : SV_InsideTessFactor;
};

#define MAX_POINTS 3

HS_CONSTANT_DATA_OUTPUT ConstantHS(
    InputPatch<VS_CONTROL_POINT_OUTPUT, MAX_POINTS> ip,
    uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT Output;
    
    Output.Edges[0] = 4.0f;
    Output.Edges[1] = 4.0f;
    Output.Edges[2] = 4.0f;
    Output.Inside = 4.0f;
    // Insert code to compute Output here

    return Output;
}

[domain("tri")]
[partitioning("fractional_even")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("ConstantHS")]
BEZIER_CONTROL_POINT main(
    InputPatch<VS_CONTROL_POINT_OUTPUT, MAX_POINTS> ip,
    uint i : SV_OutputControlPointID,
    uint PatchID : SV_PrimitiveID)
{
    VS_CONTROL_POINT_OUTPUT Output;

    Output.vPosition = ip[i].vPosition;
    Output.vUV = ip[i].vPosition;
    // Insert code to compute Output here.

    return Output;
}