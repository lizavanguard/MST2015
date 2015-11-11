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
#include "Framework/Camera/camera_manager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 100.0f;
  const char* kShadername = "object3d";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Object3D::Object3D(const char* p_filename)
    : p_shader_(nullptr)
    , p_declaration_(nullptr) {
  p_shader_ = ShaderManager::Instance().FindShader(kShadername);

  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
    {0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateVertexDeclaration(elements, &p_declaration_);

  p_texture_ = TextureManager::Instance().Find(p_filename);
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object3D::~Object3D() {
  SafeRelease(p_declaration_);
}

//------------------------------------------------
// _Update
//------------------------------------------------
void Object3D::_Update(const float elapsed_time) {
  int a = 0;
}

//------------------------------------------------
// _Draw
// HACK:
//------------------------------------------------
void Object3D::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  struct Vertex3D {
    D3DXVECTOR3 vertex;
    D3DXVECTOR4 diffuse;
    D3DXVECTOR2 texcoord;
  };
  // vertices
  const float half_x = kSize * 0.5f;
  Vertex3D data[] = {
    {D3DXVECTOR3(-half_x, kSize, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(0, 0)},  // lt
    {D3DXVECTOR3(+half_x, kSize, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(1, 0)},  // rt
    {D3DXVECTOR3(-half_x, 0.0f, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(0, 1)},  // lb
    {D3DXVECTOR3(+half_x, 0.0f, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(1, 1)},  // rb
  };

  p_device->SetVertexDeclaration(p_declaration_);

  D3DXMATRIX wvp = world_matrix_ * CameraManager::Instance().Find("MAIN_CAMERA").GetViewMatrix() * CameraManager::Instance().Find("MAIN_CAMERA").GetProjectionMatrix();
  p_shader_->SetMatrix("u_wvp", &wvp);

  p_shader_->SetTexture("texture_decale", p_texture_);

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);

  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));

  p_shader_->EndPass();
  p_shader_->End();
}
