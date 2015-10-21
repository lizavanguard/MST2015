float4x4 cWorld;
float4x4 cWVP;
float3 cLocalLightDir;
float4 cLightDiffuse;
float4 cLightAmbient = { 1.0f, 1.0f, 1.0f, 1.0f} ;
float4 cMatDiffuse;
float4 cMatAmbient;
float4 cEyeVector;

void VS(
    in float3 pos : POSITION0,
    in float3 normal : NORMAL0,
    out float4 outPos : POSITION,
    out float4 outColor : COLOR0) {
  outPos = mul(float4(pos, 1.0f), cWVP);

  // ランバート
  //float light = max(dot(normal, -cLocalLightDir), 0);

  // ハーフランバート
  //float light = dot(normal, -cLocalLightDir) * 0.5f + 0.5f;

  //float4 worldNormal = mul(normal, cWorld);
  //worldNormal = normalize(worldNormal);
  //float light = 1.0f - abs(dot(cEyeVector, worldNormal)) * 1.2f;

  outColor = /*cMatDiffuse * cLightDiffuse * light +*/ cMatAmbient * cLightAmbient;
  outColor.a = 1.0f;
}

void PS(
    in float4 color : COLOR0,
    out float4 outColor : COLOR0) {
  outColor = color;
}

technique TechShader {
  pass P0 {
    VertexShader = compile vs_2_0 VS();
    PixelShader = compile ps_2_0 PS();
  }
}