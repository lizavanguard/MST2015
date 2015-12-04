//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//
// fade.hlsl
// Author : Shimizu Shoji
//
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//==============================================================================
// uniform
//==============================================================================
uniform float u_fade_value;

texture texture_decale;
sampler sampler_decale= sampler_state {
  Texture = <texture_decale>;
  //MinFilter = LINEAR;
  //MagFilter = LINEAR;
  //MipFilter = NONE;

  //AddressU = Wrap;
  //AddressV = Wrap;
};

//==============================================================================
// shader
//==============================================================================
//------------------------------------------------
// Pixel Shader
//------------------------------------------------
void PS(in float2 in_texcoord : TEXCOORD0,
        out float4 out_color : COLOR0) {
  out_color = tex2D(sampler_decale, in_texcoord) * (1.0f - u_fade_value);
  out_color.a = 1.0f;
  //out_color = float4(1.0, 0.0, 1.0, 0.0);
}

//==============================================================================
// technique
//==============================================================================
technique TechShader {
  pass P0 {
    PixelShader = compile ps_2_0 PS();
  }
}
