//==========================================================================
// コンスタントテーブル宣言
//==========================================================================
float4x4	worldArray[52];	// スキンメッシュ用のワールド配列
float4x4	viewProj;				// カメラのビュープロジェクション
float3		lightVec;				// ライトベクトル

//==========================================================================
// 頂点シェーダー
//==========================================================================
void VS(in float3 inPos : POSITION0,
        in float3 inNor : NORMAL0,
        in float2 inUv : TEXCOORD0,
        in float inIndex : TEXCOORD1,
        out float4 outPos : POSITION,
        out float2 outUv : TEXCOORD0,
        out float outlight : TEXCOORD1) {
  int index = (int)inIndex;

  float4 tempPos = mul(float4( inPos, 1.0f ), worldArray[index]);
  outPos = mul(tempPos, viewProj);
  float3 wNor = normalize(mul(float4( inNor, 0.0f ), worldArray[index])).xyz;
  float light = dot(wNor, -lightVec);
  light = light * 0.5f + 0.5f;
  outlight = light;
  outUv = inUv;
}