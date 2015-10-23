//==============================================================================
//
// ObjectModel
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_model.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kShadername = "objectx";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectModel::ObjectModel(const char* p_filename) : p_xmodel_data_(nullptr), p_shader_(nullptr) {
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
ObjectModel::~ObjectModel() {
}


//------------------------------------------------
// _Update
//------------------------------------------------
void ObjectModel::_Update(const float elapsed_time) {
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectModel::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  auto camera = CameraManager::Instance().GetCamera(0);
  D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();

  p_shader_->SetMatrix("u_wvp", &wvp);

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);

  D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_xmodel_data_->p_materials->GetBufferPointer();
  for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
    p_shader_->SetTexture("texture_decale", p_xmodel_data_->p_textures[count_material]);
    p_shader_->CommitChanges();
    p_xmodel_data_->p_mesh->DrawSubset(count_material);
  }

  p_shader_->EndPass();
  p_shader_->End();
}
