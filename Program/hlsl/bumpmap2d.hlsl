//==============================================================================
//
// ランバート照明モデル [LambertLighting.hlsl]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// struct definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// 頂点シェーダ出力
// 頂点シェーダでライティングの計算を行うので
// 色の出力用にデータを加える
//------------------------------------------------
struct VS_Out {
  float4 pos   : POSITION;
  float4 color : COLOR0;
  float2 tex   : TEXCOORD0;
  float3 e     : TEXCOORD1;
  float3 l     : TEXCOORD2;
};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// global-variable definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
float4x4 mtxWVP;	// ワールド-ビュー-プロジェクションまで
float4x4 mtxWIT;	// ローカル座標系からワールド座標系への変換行列の 逆行列の転置行列

float4 vecLightDir;	// ライトの方向
float4 vecColor;	// ライト*メッシュの色
float3 vecEyePos;	// カメラの位置(ローカル座標系)


texture decaleTex;
sampler DecaleSamp = sampler_state
{
  Texture = <decaleTex>;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
  MipFilter = NONE;

  AddressU = Clamp;
  AddressV = Clamp;
};

texture normalMap;
sampler NormalSamp = sampler_state
{
  Texture = <normalMap>;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
  MipFilter = NONE;

  AddressU = Wrap;
  AddressV = Wrap;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// VS implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ライティングはPSで行ってます
//------------------------------------------------
VS_Out VS(
  float4 pos : POSITION,	// ローカル位置座標
  float3 normal : NORMAL,	// 法線ベクトル w成分には1が入ってくる
  float3 tangent : TANGENT0,	// 接ベクトル
  float2 tex : TEXCOORD0	// 法線ベクトル
  ) {
  // 出力データの用意
  VS_Out outData = (VS_Out)0;

  // 座標変換
  outData.pos = mul(pos, mtxWVP);

  // メッシュの色
  outData.color = vecColor;

  // デカール用のテクスチャ座標
  outData.tex = tex;

  // 座標系の基底変換
  float3 n = normal;	// 法線
    float3 t = tangent;	// 接
    float3 b = cross(n, t);	// 従法線

    // 鏡面反射用のベクトル
    float3 e = vecEyePos - pos.xyz;	// 視線ベクトル
    outData.e.x = dot(e, t);
  outData.e.y = dot(e, b);
  outData.e.z = dot(e, n);

  float3 l = -vecLightDir.xyz;		// ライトベクトル
    outData.l.x = dot(l, t);
  outData.l.y = dot(l, b);
  outData.l.z = dot(l, n);

  return outData;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PS implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// 拡散反射光 環境光 鏡面反射光
// および バンプマッピング
//------------------------------------------------
float4 PS(VS_Out inData) : COLOR{
  float3 n = 2.0f * tex2D(NormalSamp, inData.tex).xyz - 1.0f;	// 法線マップからの法線
  float3 l = normalize(inData.l);	// ライトベクトル
  float3 r = reflect(-normalize(inData.e), n);	// 反射ベクトル
  float amb = -vecLightDir.w;	// 環境光の強さ

  inData.color = inData.color * tex2D(DecaleSamp, inData.tex)	// 拡散光と環境光には
    * (max(0, dot(n, l)) + amb)					// 頂点色とテクスチャの色を合成する
    + 0.3f * pow(max(0, dot(r, l)), 8);	// Phong鏡面反射光
  inData.color.a = 1;
  return inData.color;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// technique definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
technique TestShader {
  pass P0 {
    VertexShader = compile vs_2_0 VS();
    PixelShader = compile ps_2_0 PS();
  }
}