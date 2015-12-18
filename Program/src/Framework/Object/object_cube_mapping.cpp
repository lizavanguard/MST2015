//==============================================================================
//
// ObjectCubeMapping

// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_cube_mapping.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/CubeTextureForEnvironmentMapping/CubeTextureForEnvironmentMapping.h"
#include "Framework/Light/light.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"

extern CubeTextureForEnvironmentMapping* g_p_cube_;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kShadername = "cubeMap";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectCubeMapping::ObjectCubeMapping(const char* p_filename)
    : p_xmodel_data_(nullptr)
    , p_shader_(nullptr)
    , p_cube_mapping_(nullptr)
    , is_drawn_ccw_(true)
    , is_drawn_cw_(true) {
  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  p_xmodel_data_ = ModelManager::Instance().Find(p_filename);
  liza::game::directx::AttachVertexDeclarationToMesh(DeviceHolder::Instance().GetDevice(), &p_xmodel_data_->p_mesh, elements);

  p_shader_ = ShaderManager::Instance().FindShader(kShadername);
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectCubeMapping::~ObjectCubeMapping() {
}


//------------------------------------------------
// _Update
//------------------------------------------------
void ObjectCubeMapping::_Update(const float elapsed_time) {
  position_ += speed_ * elapsed_time;
  speed_ *= 0.99f;
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectCubeMapping::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  auto& camera = CameraManager::Instance().GetMainCamera();
  const D3DXVECTOR3 light_direction = LightServiceLocator::Get()->GetDirection();

  D3DXMATRIX View = camera.GetViewMatrix();
  D3DXMATRIX Projection = camera.GetProjectionMatrix();
  D3DXMATRIX WVP = world_matrix_ * View * Projection;

  // ライトベクトルのローカル化
  D3DXMATRIX invWorld, invTransWorld;
  D3DXMatrixInverse(&invWorld, nullptr, &world_matrix_);
  D3DXMatrixTranspose(&invTransWorld, &invWorld);

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);

  p_shader_->SetMatrix("uniform_matrix_world_view_projection", &WVP);
  p_shader_->SetMatrix("uniform_matrix_world", &world_matrix_);
  D3DXVECTOR4 light_direction4(light_direction.x, light_direction.y, light_direction.z, 1.0f);
  p_shader_->SetVector("uniform_light_direction", &light_direction4);
  D3DXVECTOR4 camera_position4(camera._GetEye().x, camera._GetEye().y, camera._GetEye().z, 1.0f);
  p_shader_->SetVector("uniform_camera_position", &camera_position4);

  p_shader_->SetFloat("uniform_cube_mapping_depth", 0.8f);

  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
  if (is_drawn_cw_) {
    p_shader_->SetInt("uniform_reflect_sign", -1);
    D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_xmodel_data_->p_materials->GetBufferPointer();
    for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
      D3DXVECTOR4 color(
        p_d3dx_material[count_material].MatD3D.Diffuse.r,
        p_d3dx_material[count_material].MatD3D.Diffuse.g,
        p_d3dx_material[count_material].MatD3D.Diffuse.b,
        p_d3dx_material[count_material].MatD3D.Diffuse.a);
      p_shader_->SetVector("uniform_diffuse", &color);
      p_shader_->SetTexture("texture_decale", p_xmodel_data_->p_textures[count_material]);
      p_shader_->SetTexture("cube_decale", g_p_cube_->GetCubeTexture());
      p_shader_->CommitChanges();
      p_xmodel_data_->p_mesh->DrawSubset(count_material);
    }
  }

  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
  if (is_drawn_ccw_) {
    p_shader_->SetInt("uniform_reflect_sign", 1);
    D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_xmodel_data_->p_materials->GetBufferPointer();
    for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
      D3DXVECTOR4 color(
        p_d3dx_material[count_material].MatD3D.Diffuse.r,
        p_d3dx_material[count_material].MatD3D.Diffuse.g,
        p_d3dx_material[count_material].MatD3D.Diffuse.b,
        p_d3dx_material[count_material].MatD3D.Diffuse.a);
      p_shader_->SetVector("uniform_diffuse", &color);
      p_shader_->SetTexture("texture_decale", p_xmodel_data_->p_textures[count_material]);
      p_shader_->SetTexture("cube_decale", g_p_cube_->GetCubeTexture());
      p_shader_->CommitChanges();
      p_xmodel_data_->p_mesh->DrawSubset(count_material);
    }
  }

  p_shader_->EndPass();
  p_shader_->End();
}
