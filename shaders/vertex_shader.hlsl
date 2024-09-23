struct VSOut
{
    float3 color : Color;
    float4 pos : SV_Position;
};

cbuffer Cbuffer
{
    matrix transform;
};

VSOut main(float2 pos : Position, float3 color : Color)
{
    VSOut vso;
    vso.pos = mul(float4(pos.xy, 0.0f, 1.0f), transform);
    vso.color = color;
    return vso;
};
