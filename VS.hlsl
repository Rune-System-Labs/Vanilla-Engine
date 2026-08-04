cbuffer Transform : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    output.position = mul(float4(input.position, 1.0f), World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.uv = input.uv;
    return output;
}
