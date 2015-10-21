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
#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectModel::ObjectModel(const char* p_filename) {
  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  auto p_device = DeviceHolder::Instance().GetDevice();

  liza::game::directx::LoadMeshFromX(
    p_device,
    p_filename,
    &p_mesh_,
    &p_materials_,
    &num_materials_);

  liza::game::directx::AttachVertexDeclarationToMesh(p_device, &p_mesh_, elements);

  
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectModel::~ObjectModel() {
  SafeRelease(p_materials_);
  SafeRelease(p_mesh_);
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

  // HACK: 
  D3DXMATRIX view;
  D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(0, 10, -100), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
  p_device->SetTransform(D3DTS_VIEW, &view);

  D3DXMATRIX projection;
  D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI * 0.5f, 1280 / 760.0f, 1.0f, 1000.0f); // TEKITOU
  p_device->SetTransform(D3DTS_PROJECTION, &projection);

  // WVP
  D3DXMATRIX mtx_world;
  //D3DXMatrixTranslation(&mtx_world, position_.x, position_.y, position_.z);
  D3DXMatrixIdentity(&mtx_world);
  p_device->SetTransform(D3DTS_WORLD, &mtx_world);

  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

  // set texture
  p_device->SetTexture(0, nullptr);

  for (unsigned int count_material = 0; count_material < num_materials_; ++count_material) {
    p_mesh_->DrawSubset(count_material);
  }

  //p_device->Set
}
