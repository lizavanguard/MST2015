//==============================================================================
//
// �����o�[�g�Ɩ����f�� [LambertLighting.hlsl]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// struct definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ���_�V�F�[�_�o��
// ���_�V�F�[�_�Ń��C�e�B���O�̌v�Z���s���̂�
// �F�̏o�͗p�Ƀf�[�^��������
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
float4x4 mtxWVP;	// ���[���h-�r���[-�v���W�F�N�V�����܂�
float4x4 mtxWIT;	// ���[�J�����W�n���烏�[���h���W�n�ւ̕ϊ��s��� �t�s��̓]�u�s��

float4 vecLightDir;	// ���C�g�̕���
float4 vecColor;	// ���C�g*���b�V���̐F
float3 vecEyePos;	// �J�����̈ʒu(���[�J�����W�n)


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
// ���C�e�B���O��PS�ōs���Ă܂�
//------------------------------------------------
VS_Out VS(
  float4 pos : POSITION,	// ���[�J���ʒu���W
  float3 normal : NORMAL,	// �@���x�N�g�� w�����ɂ�1�������Ă���
  float3 tangent : TANGENT0,	// �ڃx�N�g��
  float2 tex : TEXCOORD0	// �@���x�N�g��
  ) {
  // �o�̓f�[�^�̗p��
  VS_Out outData = (VS_Out)0;

  // ���W�ϊ�
  outData.pos = mul(pos, mtxWVP);

  // ���b�V���̐F
  outData.color = vecColor;

  // �f�J�[���p�̃e�N�X�`�����W
  outData.tex = tex;

  // ���W�n�̊��ϊ�
  float3 n = normal;	// �@��
    float3 t = tangent;	// ��
    float3 b = cross(n, t);	// �]�@��

    // ���ʔ��˗p�̃x�N�g��
    float3 e = vecEyePos - pos.xyz;	// �����x�N�g��
    outData.e.x = dot(e, t);
  outData.e.y = dot(e, b);
  outData.e.z = dot(e, n);

  float3 l = -vecLightDir.xyz;		// ���C�g�x�N�g��
    outData.l.x = dot(l, t);
  outData.l.y = dot(l, b);
  outData.l.z = dot(l, n);

  return outData;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PS implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// �g�U���ˌ� ���� ���ʔ��ˌ�
// ����� �o���v�}�b�s���O
//------------------------------------------------
float4 PS(VS_Out inData) : COLOR{
  float3 n = 2.0f * tex2D(NormalSamp, inData.tex).xyz - 1.0f;	// �@���}�b�v����̖@��
  float3 l = normalize(inData.l);	// ���C�g�x�N�g��
  float3 r = reflect(-normalize(inData.e), n);	// ���˃x�N�g��
  float amb = -vecLightDir.w;	// �����̋���

  inData.color = inData.color * tex2D(DecaleSamp, inData.tex)	// �g�U���Ɗ����ɂ�
    * (max(0, dot(n, l)) + amb)					// ���_�F�ƃe�N�X�`���̐F����������
    + 0.3f * pow(max(0, dot(r, l)), 8);	// Phong���ʔ��ˌ�
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