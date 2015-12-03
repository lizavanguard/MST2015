//==========================================================================
// �R���X�^���g�e�[�u���錾
//==========================================================================
sampler DiffuseSampler;
sampler ToonSampler;

//==========================================================================
// ���_�V�F�[�_�[
//==========================================================================
float4 PS(in float2 inUv : TEXCOORD0,
          in float inlight : TEXCOORD1,
          in float2 inToonUV : TEXCOORD2) : COLOR0
{
  //float4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
  float4 color = tex2D(DiffuseSampler, inUv) * tex2D(ToonSampler, inToonUV);
  return float4( ( color * inlight ).rgb, color.a );
}