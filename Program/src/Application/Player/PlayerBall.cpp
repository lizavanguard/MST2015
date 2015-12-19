//==============================================================================
//
// PlayerBall
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "PlayerBall.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kModelname = "ball_03";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
PlayerBall::PlayerBall(CubeTextureForEnvironmentMapping::ObjectDrawer* p_object_drawer)
  : ObjectCubeMapping(kModelname, p_object_drawer)
  , rotation_power_(0.0f)
  , rotation_axis_(0.0f, 0.0f, 0.0f) {
  Reset();
}

//------------------------------------------------
// dtor
//------------------------------------------------
PlayerBall::~PlayerBall() {
}

//------------------------------------------------
// Reset
//------------------------------------------------
void PlayerBall::Reset(void) {
  rotation_power_ = 0.0f;
  rotation_axis_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

//------------------------------------------------
// Shoot
//------------------------------------------------
void PlayerBall::Shoot(const float rotation) {
  // ‰ñ“]—Ê‚Ì’²®
  const float kMaxRotationPower = 4.0f;
  const float kMaxRotation = D3DX_PI * 0.25f;
  const float fixed_rotation = -(kMaxRotation * (rotation / kMaxRotationPower));
  rotation_axis_.x = cosf(fixed_rotation);
  rotation_axis_.y = sinf(fixed_rotation);
}

//------------------------------------------------
// Update
//------------------------------------------------
void PlayerBall::_Update(const float elapsed_time) {
  // ƒ{[ƒ‹‚Ì‰ñ“]
  D3DXQUATERNION q;
  D3DXQuaternionRotationAxis(&q, &rotation_axis_, rotation_power_);

  D3DXMATRIX rotation_matrix;
  D3DXMatrixRotationQuaternion(&rotation_matrix, &q);

  //position_ = GetWorldPosition();
  rotation_matrix_ = rotation_matrix;
}

////------------------------------------------------
//// Draw
////------------------------------------------------
//void PlayerBall::_Draw(void) {
//  auto p_device = DeviceHolder::Instance().GetDevice();
//  auto& camera = CameraManager::Instance().GetMainCamera();
//  D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();
//
//  p_shader_->SetMatrix("u_wvp", &wvp);
//
//  p_shader_->Begin(nullptr, 0);
//  p_shader_->BeginPass(0);
//
//  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
//  D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_xmodel_data_->p_materials->GetBufferPointer();
//  for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
//    p_shader_->SetTexture("texture_decale", p_xmodel_data_->p_textures[count_material]);
//    p_shader_->CommitChanges();
//    p_xmodel_data_->p_mesh->DrawSubset(count_material);
//  }
//
//  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//  for (unsigned int count_material = 0; count_material < p_xmodel_data_->num_materials; ++count_material) {
//    p_shader_->SetTexture("texture_decale", p_xmodel_data_->p_textures[count_material]);
//    p_shader_->CommitChanges();
//    p_xmodel_data_->p_mesh->DrawSubset(count_material);
//  }
//
//  p_shader_->EndPass();
//  p_shader_->End();
//}

//------------------------------------------------
// Change
//------------------------------------------------
void PlayerBall::ChangeDrawingOuterFace(const bool is_drawn_outer_face) {
  if (is_drawn_outer_face) {
    this->ObjectCubeMapping::OnDrawingCCW();
  }
  else {
    this->ObjectCubeMapping::OffDrawingCCW();
  }
}
