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

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"

#include "Framework/Light/light.h"

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

  ID3DXMesh* pTempMesh = NULL;
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_xmodel_data_->p_mesh->CloneMeshFVF(p_xmodel_data_->p_mesh->GetOptions(),
                                       p_xmodel_data_->p_mesh->GetFVF() | D3DFVF_NORMAL, p_device, &pTempMesh);

  D3DXComputeNormals(pTempMesh, NULL);
  p_xmodel_data_->p_mesh->Release();
  p_xmodel_data_->p_mesh = pTempMesh;

  p_xmodel_data_->p_mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, nullptr, nullptr, nullptr, nullptr);

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
  position_ += speed_ * elapsed_time;
  speed_ *= 0.99f;
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectModel::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  auto& camera = CameraManager::Instance().GetMainCamera();
  D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();

  p_shader_->SetMatrix("u_wvp", &wvp);

  const D3DXVECTOR3 light_direction = LightServiceLocator::Get()->GetDirection();
  const float light_ambient = LightServiceLocator::Get()->GetAmbient();
  D3DXVECTOR4 light_direction4(light_direction.x, light_direction.y, light_direction.z, light_ambient);
  p_shader_->SetVector("u_light_information", &light_direction4);

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
