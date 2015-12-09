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
PlayerBall::PlayerBall()
  : ObjectModel(kModelname)
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
  // âÒì]ó ÇÃí≤êÆ
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
  // É{Å[ÉãÇÃâÒì]
  D3DXQUATERNION q;
  D3DXQuaternionRotationAxis(&q, &rotation_axis_, rotation_power_);

  D3DXMATRIX rotation_matrix;
  D3DXMatrixRotationQuaternion(&rotation_matrix, &q);

  //position_ = GetWorldPosition();
  rotation_matrix_ = rotation_matrix;
}
