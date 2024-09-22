float4 main(float3 color : Color) : SV_Target
{
    return float4(color.rgb, 1.0f); // Output white color
}

