//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//
// object3d.hlsl
// Author : Shimizu Shoji
//
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//==============================================================================
// uniform
//==============================================================================
uniform float4x4 u_wvp;

texture texture_decale;
sampler sampler_decale= sampler_state {
  Texture = <texture_decale>;
};

uniform float4 u_light_information;  // float.xyz=direction, w=ambient;

//==============================================================================
// shader
//==============================================================================
//------------------------------------------------
// Vertex Shder
//------------------------------------------------
void VS(in float3 in_position : POSITION0,
        in float3 in_normal : NORMAL0,
        in float2 in_texcoord : TEXCOORD0,
        out float4 out_position : POSITION,
        out float2 out_texcoord : TEXCOORD0,
        out float  out_light_power : TEXCOORD1) {
  out_position = mul(float4(in_position, 1.0f), u_wvp);

  out_texcoord = in_texcoord;

  // TODO: light
  out_light_power = dot(normalize(in_normal), normalize(float3(-u_light_information.xyz))) * 0.5f + 0.5f;
}

//------------------------------------------------
// Pixel Shader
//------------------------------------------------
void PS(in float4 in_color : COLOR0,
        in float2 in_texcoord : TEXCOORD0,
        in float  in_light_power : TEXCOORD1,
        out float4 out_color : COLOR0) {
  out_color = tex2D(sampler_decale, in_texcoord) * in_color * in_light_power;
  out_color += u_light_information.w;
  out_color = min(out_color, 1.0f);
  out_color.a = 1.0f;
}

//==============================================================================
// technique
//==============================================================================
technique TechShader {
  pass P0 {
    VertexShader = compile vs_2_0 VS();
    PixelShader = compile ps_2_0 PS();
  }
}
