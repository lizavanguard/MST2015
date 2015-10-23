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

#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectModel::ObjectModel(const char* p_filename) : p_xmodel_data_(nullptr) {
  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  auto p_device = DeviceHolder::Instance().GetDevice();

  p_xmodel_data_ = ModelManager::Instance().Find(p_filename);

  liza::game::directx::AttachVertexDeclarationToMesh(p_device, &p_xmodel_data_->p_mesh, elements);

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

  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  p_device->SetTransform(D3DTS_WORLD, &world_matrix_);

  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

  // set texture

  D3DMATERIAL9 material_old;
  p_device->GetMaterial(&material_old);
  D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_xmodel_data_->p_materials->GetBufferPointer();
  for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
    D3DMATERIAL9 material;
    ZeroMemory(&material, sizeof(material));
    material.Diffuse = D3DXCOLOR(D3DCOLOR_RGBA(128, 128, 255, 255));
    p_device->SetMaterial(&material);
    p_device->SetTexture(0, p_xmodel_data_->p_textures[count_material]);
    p_xmodel_data_->p_mesh->DrawSubset(count_material);
  }
  p_device->SetMaterial(&material_old);

  //p_device->Set
}
