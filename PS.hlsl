Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 main(PixelInput input) : SV_TARGET
{
    return diffuseTexture.Sample(diffuseSampler, input.uv);
}
