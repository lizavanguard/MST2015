//==============================================================================
//
// Standard2D
// Author : Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
uniform float4 cColor = {1.0f, 1.0f, 1.0f, 1.0f};
uniform float3 cVectorLightDirection = {1.0f, 1.0f, 1.0f};  // 光の方向(光への方向ではない)(ローカル)
uniform float cAmbient = 0.2f;

uniform texture cTextureStandard;
sampler cSamplerStandard = sampler_state {
  Texture = <cTextureStandard>;
};

uniform texture cTextureNormal;
sampler cSamplerNormal = sampler_state {
  Texture = <cTextureNormal>;
};

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// pass0
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//------------------------------------------------
// PS
//------------------------------------------------
void PS(in float2 texcoord : TEXCOORD0,
        out float4 outColor : COLOR0) {
  const float4 texture_color = tex2D(cSamplerStandard, texcoord);

  // 法線マップの値から法線を復元する
  const float3 normal = 2.0f * tex2D(cSamplerNormal, texcoord).xyz - 1.0f;
  const float3 vector_light = normalize(cVectorLightDirection);
  const float4 lighing_color = max(0, dot(normal, vector_light)) * cColor;

  outColor = texture_color * lighing_color;
  outColor.a = 1.0f;
}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// technique
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
technique Technique0 {
  pass Pass0 {
    PixelShader = compile ps_2_0 PS();
  }
}
