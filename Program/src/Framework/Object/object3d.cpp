//==============================================================================
//
// Object3D
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object3D.h"

#include "Framework/Utility/DeviceHolder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 100.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Object3D::Object3D(int) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object3D::~Object3D() {
}

//------------------------------------------------
// _Update
//------------------------------------------------
void Object3D::_Update(const float elapsed_time) {
}

//------------------------------------------------
// _Draw
// HACK:
//------------------------------------------------
void Object3D::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  // turn lighting off
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);
  //p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

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

  struct Vertex3D {
    D3DXVECTOR3 position;
    DWORD diffuse;
    D3DXVECTOR2 texcoord;
  };

  // vertices
  const float half_x = kSize * 0.5f;
  Vertex3D data[] = {
    {D3DXVECTOR3(-half_x, kSize, 0.0f), 0xffffffff, D3DXVECTOR2(0, 0)},  // lt
    {D3DXVECTOR3(+half_x, kSize, 0.0f), 0xffffffff, D3DXVECTOR2(1, 0)},  // rt
    {D3DXVECTOR3(-half_x, 0.0f, 0.0f), 0xffffffff, D3DXVECTOR2(0, 1)},  // lb
    {D3DXVECTOR3(+half_x, 0.0f, 0.0f), 0xffffffff, D3DXVECTOR2(1, 1)},  // rb
  };

  // set texture
  p_device->SetTexture(0, nullptr);

  // set fvf
  p_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

  // draw
  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));
}
