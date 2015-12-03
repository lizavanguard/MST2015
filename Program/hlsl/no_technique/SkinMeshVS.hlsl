//==========================================================================
// コンスタントテーブル宣言
//==========================================================================
float4x4	worldArray[52];	// スキンメッシュ用のワールド配列
float4x4	viewProj;				// カメラのビュープロジェクション
float3		lightVec;				// ライトベクトル
float3    cameraDir;	      // カメラ方向

//==========================================================================
// 頂点シェーダー
//==========================================================================
void VS(in float3 inPos : POSITION0,
        in float3 inBlendWeight : BLENDWEIGHT0,
        in float4 inBlendIndex : BLENDINDICES,
		    in float3 inNor : NORMAL0,
		    in float2 inUv : TEXCOORD0,

		    out float4 outPos : POSITION,
		    out float2 outUv : TEXCOORD0,
		    out float outlight : TEXCOORD1,
        out float2 outToonUV : TEXCOORD2)
{
	int index0, index1, index2, index3;
	float weight0, weight1, weight2, weight3;
	float4x4 world0, world1, world2, world3;

	index0 = inBlendIndex.x;
	index1 = inBlendIndex.y;
	index2 = inBlendIndex.z;
	index3 = inBlendIndex.w;

	weight0 = inBlendWeight.x;
	weight1 = inBlendWeight.y;
	weight2 = inBlendWeight.z;
	weight3 = 1.0f - weight0 - weight1 - weight2;

	world0 = worldArray[index0];
	world1 = worldArray[index1];
	world2 = worldArray[index2];
	world3 = worldArray[index3];

	//worldとvpをかけあわせろ！
	float4x4 world = world0 * weight0
				   + world1 * weight1
				   + world2 * weight2
				   + world3 * weight3;

	float4 tempPos = mul(float4(inPos, 1.0f), world);
	outPos = mul(tempPos, viewProj);
	float3 wNor = normalize(mul(float4(inNor, 0.0f), world)).xyz;
	float light = dot(wNor, -lightVec);
	light = light * 0.5f + 0.5f;
  outlight = light;
	outUv = inUv;

  outToonUV.x = light;
  outToonUV.y = 0.1f - dot(cameraDir, inNor) * 0.3f;
}