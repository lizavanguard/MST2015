//==========================================================
// �萔���W�X�^ CPU������ύX�ł��鐔���Ȃ�����
//==========================================================
texture texture_decale;
sampler uniform_texture_sampler = sampler_state {
  Texture = <texture_decale>;
};
texture cube_decale;
samplerCUBE uniform_cube_sampler = sampler_state {
  Texture = <cube_decale>;
};

float3 uniform_light_direction;                   // ���[���h���C�g����

float4x4 uniform_matrix_world_view_projection;    // ���W�ϊ��s��
float4x4 uniform_matrix_world;                    // ���W�ϊ��s��
float3 uniform_camera_position;                   // ���C�g����
float4 uniform_diffuse;                           // �}�e���A���F

int uniform_reflect_sign;
float uniform_cube_mapping_depth;

//*****************************************************************************
// �G���g���|�C���g
//*****************************************************************************
void VS(in float3 in_position   : POSITION0
  , in float3 in_normal : NORMAL0
  , in float2 in_texcoord : TEXCOORD0
  , out float4 out_position : POSITION
  , out float2 out_texcoord : TEXCOORD0
  , out float3 out_world_normal : TEXCOORD1
  , out float3 out_world_view_vector : TEXCOORD2)
{
  // ���[���h�@��
  out_world_normal = normalize(mul(float4(normalize(in_normal), 0.0f), uniform_matrix_world));
  out_position = mul(float4(in_position, 1.0f), uniform_matrix_world_view_projection);
  out_texcoord = in_texcoord;
  float3 world_position = mul(float4(in_position, 1.0f), uniform_matrix_world).xyz;

  out_world_view_vector = world_position - uniform_camera_position;
}
// EOF

//**********************************************************
// �G���g���|�C���g
//**********************************************************
float4 PS(float2 texcoord : TEXCOORD0, float3 world_normal : TEXCOORD1, float3 world_view_vector : TEXCOORD2) : COLOR0
{
  float3 normal = normalize(world_normal);
  float3 toEye = normalize(world_view_vector);
  float3 vReflect = reflect(toEye, normal) * uniform_reflect_sign;
  float4 color = (1 - uniform_cube_mapping_depth) * tex2D(uniform_texture_sampler, texcoord)
                    + uniform_cube_mapping_depth  * texCUBE(uniform_cube_sampler, vReflect);

  float distToEye = length(toEye);
  toEye /= distToEye;
  // �X�y�L�����[���C�g
  float3 r = reflect(normalize(uniform_light_direction), normal);
  float s = pow(max(dot(r, toEye), 0.0f), 50.0f);
  float light = dot(normalize(uniform_light_direction), normal);
  light = light * 0.5f + 0.5f;
  color *= light;
  color += s * ( 1 - uniform_reflect_sign) * 0.5f;
  return color;
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

// EOF