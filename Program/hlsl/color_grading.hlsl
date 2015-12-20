//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//
// color_grading.hlsl
// Author : Shimizu Shoji
//
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//==============================================================================
// uniform
//==============================================================================
uniform float3 uniform_ycbcr_rate = float3(1.0f, 1.0f, 1.0f);

texture texture_decale;
sampler sampler_decale = sampler_state {
  Texture = <texture_decale>;
};

//==============================================================================
// function
//==============================================================================
float3 ToYCbCr(float3 color);
float3 ToColor(float3 ycbcr);

//==============================================================================
// shader
//==============================================================================
//------------------------------------------------
// Pixel Shader
//------------------------------------------------
void PS(in float2 in_texcoord : TEXCOORD0,
        out float4 out_color : COLOR0) {
  float4 texture_color = tex2D(sampler_decale, in_texcoord);

  float3 ycbcr = ToYCbCr(texture_color.xyz);
  ycbcr *= uniform_ycbcr_rate;
  float3 color = ToColor(ycbcr);

    //out_color = float4(1, 1, 1, 1.0f);
  out_color = float4(color.x, color.y, color.z, 1.0f);
}

//==============================================================================
// technique
//==============================================================================
technique TechShader {
  pass P0 {
    PixelShader = compile ps_2_0 PS();
  }
}

//==============================================================================
// function implementation
//==============================================================================
float3 ToYCbCr(float3 color) {
  return float3(
     0.2989f * color.r + 0.5866f  * color.g + 0.1145f  * color.b,
    -0.1687f * color.r - 0.33126f * color.g + 0.5f     * color.b,
     0.5f    * color.r - 0.41869f * color.g - 0.08131f * color.b);
}

float3 ToColor(float3 ycbcr) {
  return float3(
    ycbcr.x + 1.402f   * ycbcr.z,
    ycbcr.x - 0.34414f * ycbcr.y - 0.71414f * ycbcr.z,
    ycbcr.x + 1.772f   * ycbcr.y);
}
