//==============================================================================
//
// Object2D
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2D.h"

#include "Framework/Camera/camera.h"
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 100.0f;
  const float kSizeHalf = kSize * 0.5f;
  const char* kShadername = "object3d";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Object2D::Object2D(const char* p_filename)
  : p_shader_(nullptr)
  , p_declaration_(nullptr)
  , p_texture_(nullptr)
  , is_bottom_centered_(true) {
  p_shader_ = ShaderManager::Instance().FindShader(kShadername);

  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0},
    {0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
    {0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateVertexDeclaration(elements, &p_declaration_);

  p_texture_ = TextureManager::Instance().Find(p_filename);
  uv_left_top_.x = 0.0f;
  uv_left_top_.y = 0.0f;
  uv_right_bottom_.x = 1.0f;
  uv_right_bottom_.y = 1.0f;
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object2D::~Object2D() {
  SafeRelease(p_declaration_);
}

//------------------------------------------------
// _Update
//------------------------------------------------
void Object2D::_Update(const float elapsed_time) {
  int a = 0;
}

//------------------------------------------------
// _Draw
// HACK:
//------------------------------------------------
void Object2D::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  struct Vertex3D {
    D3DXVECTOR4 vertex;
    D3DXVECTOR4 diffuse;
    D3DXVECTOR2 texcoord;
  };
  // vertices
  Vertex3D data[] = {
    {D3DXVECTOR4(position_.x - kSizeHalf, position_.y - kSizeHalf, 0.0f, 1.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(    uv_left_top_.x,     uv_left_top_.y)},  // lt
    {D3DXVECTOR4(position_.x + kSizeHalf, position_.y - kSizeHalf, 0.0f, 1.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(uv_right_bottom_.x,     uv_left_top_.y)},  // rt
    {D3DXVECTOR4(position_.x - kSizeHalf, position_.y + kSizeHalf, 0.0f, 1.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(    uv_left_top_.x, uv_right_bottom_.y)},  // lb
    {D3DXVECTOR4(position_.x + kSizeHalf, position_.y + kSizeHalf, 0.0f, 1.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(uv_right_bottom_.x, uv_right_bottom_.y)},  // rb
  };
  if (is_bottom_centered_) {
    data[0].vertex.y = position_.y - kSize;
    data[1].vertex.y = position_.y - kSize;
    data[3].vertex.y = position_.y;
    data[2].vertex.y = position_.y;
  }

  p_device->SetVertexDeclaration(p_declaration_);
  p_device->SetTransform(D3DTS_WORLD, &world_matrix_);

  //auto& camera = CameraManager::Instance().FindUsingHandle(camera_handle_);
  //D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();
  //p_shader_->SetMatrix("u_wvp", &wvp);

  //p_shader_->SetTexture("texture_decale", p_texture_);

  //p_shader_->Begin(nullptr, 0);
  //p_shader_->BeginPass(0);

  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));

  //p_shader_->EndPass();
  //p_shader_->End();
}
