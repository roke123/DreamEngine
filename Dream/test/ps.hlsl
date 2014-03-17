
Texture2D colorMap : register( t0 );
Texture2D secondMap : register( t1 );
SamplerState colorSampler : register( s0 );

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float2 tex0 : TEXCOORD;
};


float4 main( PS_Input frag ) : SV_TARGET
{
    float4 col = colorMap.Sample( colorSampler, frag.tex0 );
    float4 col2 = secondMap.Sample( colorSampler, frag.tex0 );

    return col;
}