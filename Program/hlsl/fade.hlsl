//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//
// fade.hlsl
// Author : Shimizu Shoji
//
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//==============================================================================
// uniform
//==============================================================================
uniform float alpha;

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
  out_color = tex2D(sampler_decale, in_texcoord);
  out_color.a = alpha;
}

//==============================================================================
// technique
//==============================================================================
technique TechShader {
  pass P0 {
    PixelShader = compile ps_2_0 PS();
  }
}
