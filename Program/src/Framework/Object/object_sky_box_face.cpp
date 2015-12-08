//==============================================================================
//
// ObjectSkyBoxFace
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_sky_box_face.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_config.h"
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 100.0f;
  const float kSizeHalf = kSize * 0.5f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectSkyBoxFace::ObjectSkyBoxFace(const char* p_filename) : Object3D(p_filename), skybox_camera_handle_(0) {
  skybox_camera_handle_ = CameraManager::Instance().GetCameraHandle(kSkyboxCameraName);
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectSkyBoxFace::~ObjectSkyBoxFace() {
}

//------------------------------------------------
// _Draw
// HACK:
//------------------------------------------------
void ObjectSkyBoxFace::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  struct Vertex3D {
    D3DXVECTOR3 vertex;
    D3DXVECTOR4 diffuse;
    D3DXVECTOR2 texcoord;
  };
  // vertices
  Vertex3D data[] = {
    {D3DXVECTOR3(-kSizeHalf, +kSizeHalf, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(    uv_left_top_.x,     uv_left_top_.y)},  // lt
    {D3DXVECTOR3(+kSizeHalf, +kSizeHalf, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(uv_right_bottom_.x,     uv_left_top_.y)},  // rt
    {D3DXVECTOR3(-kSizeHalf, -kSizeHalf, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(    uv_left_top_.x, uv_right_bottom_.y)},  // lb
    {D3DXVECTOR3(+kSizeHalf, -kSizeHalf, 0.0f), D3DXCOLOR(0xffffffff), D3DXVECTOR2(uv_right_bottom_.x, uv_right_bottom_.y)},  // rb
  };
  if (is_bottom_centered_) {
    data[0].vertex.y = kSize;
    data[1].vertex.y = kSize;
    data[3].vertex.y = 0.0f;
    data[2].vertex.y = 0.0f;
  }

  p_device->SetVertexDeclaration(p_declaration_);

  auto& camera = CameraManager::Instance().FindUsingHandle(skybox_camera_handle_);
  D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();
  p_shader_->SetMatrix("u_wvp", &wvp);

  p_shader_->SetTexture("texture_decale", p_texture_);

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);

  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));

  p_shader_->EndPass();
  p_shader_->End();
}
