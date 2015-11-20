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
#include "Framework/Steering/Object2D/Object2DSteering.h"

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
Object2D::Object2D(const char* p_filename, const D3DXVECTOR3& position, const D3DXVECTOR2& size, Object2DSteering* p_steering)
    : p_shader_(nullptr)
    , p_declaration_(nullptr)
    , p_texture_(nullptr)
    , size_(size)
    , alpha_(1.0f)
    , uv_left_top_(0.0f, 0.0f)
    , uv_right_bottom_(0.0f, 0.0f)
    , p_steering_(p_steering) {
  position_ = position;
  p_shader_ = ShaderManager::Instance().FindShader(kShadername);

  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0},
    {0, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
    {0, 32, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateVertexDeclaration(elements, &p_declaration_);

  p_texture_ = TextureManager::Instance().Find(p_filename);
  uv_left_top_.x = 0.0f;
  uv_left_top_.y = 0.0f;
  uv_right_bottom_.x = 1.0f;
  uv_right_bottom_.y = 1.0f;

  if (!p_steering_) {
    p_steering_ = new NullObject2DSteering();
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object2D::~Object2D() {
  SafeDelete(p_steering_);
  SafeRelease(p_declaration_);
}

//------------------------------------------------
// _Update
//------------------------------------------------
void Object2D::_Update(const float elapsed_time) {
  p_steering_->Update(*this, elapsed_time);
}

//------------------------------------------------
// _Draw
// HACK:
//------------------------------------------------
void Object2D::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  struct _Vertex3D {
    D3DXVECTOR4 vertex;
    D3DXVECTOR4 diffuse;
    D3DXVECTOR2 texcoord;
  };

  D3DXVECTOR2 half_size = size_ * 0.5f;
  // vertices
  _Vertex3D data[] = {
    {D3DXVECTOR4(position_.x - half_size.x, position_.y - half_size.y, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha_), D3DXVECTOR2(        uv_left_top_.x, uv_left_top_.y)},  // lt
    {D3DXVECTOR4(position_.x + half_size.x, position_.y - half_size.y, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha_), D3DXVECTOR2(uv_right_bottom_.x, uv_left_top_.y)},  // rt
    {D3DXVECTOR4(position_.x - half_size.x, position_.y + half_size.y, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha_), D3DXVECTOR2(uv_left_top_.x, uv_right_bottom_.y)},  // lb
    {D3DXVECTOR4(position_.x + half_size.x, position_.y + half_size.y, 0.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha_), D3DXVECTOR2(uv_right_bottom_.x, uv_right_bottom_.y)},  // rb
  };

  p_device->SetVertexDeclaration(p_declaration_);
  p_device->SetTransform(D3DTS_WORLD, &world_matrix_);

  //auto& camera = CameraManager::Instance().FindUsingHandle(camera_handle_);
  //D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();
  //p_shader_->SetMatrix("u_wvp", &wvp);

  //p_shader_->SetTexture("texture_decale", p_texture_);

  //p_shader_->Begin(nullptr, 0);
  //p_shader_->BeginPass(0);
  p_device->SetTexture(0, p_texture_);
  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(_Vertex3D));

  //p_shader_->EndPass();
  //p_shader_->End();
}
