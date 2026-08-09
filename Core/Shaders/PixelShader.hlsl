Texture2D texture : register(t0);
sampler samplerState : register(s0);

struct Pixel_in
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

float4 PSMain(Pixel_in input) : SV_TARGET
{
    float4 color = texture.Sample(samplerState, input.TexCoord.xy);
    return color;
}
