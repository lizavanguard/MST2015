//==============================================================================
//
// Player
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Player.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kModelname = "ball_02.fbx";
  const float kSize = 3.0f;

  const float kMovingSpeed = 0.3f;

  const float kAdjustedValueRotationToPower = 15.0f;
  const float kCurveReaction = 0.025f;
  //const float kCurveReaction = 0.1f;
  const float kShotSpeed = 200.0f;

  const Vector3 kStartPosition(0.0f, 1.0f, -100.0f);
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player()
    : ObjectFBXModel(kModelname)
    , CollisionObject(kSize)
    , is_shot_(false)
    , speed_(0.0f, 0.0f, 0.0f)
    , adjusted_value_(kAdjustedValueRotationToPower)
    , curve_reaction_(kCurveReaction)
    , shot_speed_(kShotSpeed)
    , moving_speed_(kMovingSpeed)
    , rotation_power_(0.0f)
    , rotation_axis_(1.0f, 0.0f, 0.0f) {
  Reset();
}

//------------------------------------------------
// dtor
//------------------------------------------------
Player::~Player() {
}

//------------------------------------------------
// Move
//------------------------------------------------
void Player::MoveLeft(void) {
  speed_.x -= moving_speed_;
}

void Player::MoveRight(void) {
  speed_.x += moving_speed_;
}

//------------------------------------------------
// Shoot
//------------------------------------------------
void Player::Shoot(const float rotation) {
  if (is_shot_) {
    return;
  }

  speed_.z += shot_speed_;

  const float true_power = -rotation * adjusted_value_;
  speed_.x = true_power;
  velocity_.x -= true_power * curve_reaction_;

  // 回転量の調整
  const float kMaxRotationPower = 4.0f;
  const float kMaxRotation = D3DX_PI * 0.25f;
  const float fixed_rotation = -(kMaxRotation * (rotation / kMaxRotationPower));
  rotation_axis_.x = cosf(fixed_rotation);
  rotation_axis_.y = sinf(fixed_rotation);

  is_shot_ = true;
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Player::Reset(void) {
  is_shot_ = false;
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  position_ = kStartPosition;
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  rotation_power_ = 0;
  rotation_axis_ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

//------------------------------------------------
// React collision
//------------------------------------------------
void Player::ReactCollision(const D3DXVECTOR3&) {
  return;
}

//------------------------------------------------
// Update
//------------------------------------------------
void Player::_Update(const float elapsed_time) {
#ifdef _DEBUG
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeed = 1.0f;
  const float true_speed = kSpeed /** elapsed_time*/;

  if (keyboard.IsPress(DIK_W)) {
    speed_.z += true_speed;
  }
  if (keyboard.IsPress(DIK_S)) {
    speed_.z -= true_speed;
  }
  if (keyboard.IsPress(DIK_I)) {
    speed_.y += true_speed;
  }
  if (keyboard.IsPress(DIK_K)) {
    speed_.y -= true_speed;
  }

  if (keyboard.IsPress(DIK_3)) { curve_reaction_+= 0.0003f; }
  if (keyboard.IsPress(DIK_4)) { curve_reaction_ -= 0.0003f; }
  if (keyboard.IsPress(DIK_5)) { shot_speed_ += 0.1f; }
  if (keyboard.IsPress(DIK_6)) { shot_speed_ -= 0.1f; }
  if (keyboard.IsPress(DIK_7)) { adjusted_value_ += 0.1f; }
  if (keyboard.IsPress(DIK_8)) { adjusted_value_ -= 0.1f; }

  DebugProc::Print("曲がり方:[%.3f]\n射出力:[%.3f]\n曲がり方の調整値:[%.3f]\n", curve_reaction_, shot_speed_, adjusted_value_);

#endif

  velocity_ *= 0.998f;
  speed_ += velocity_;
  speed_ *= 0.998f;
  position_ += speed_ * elapsed_time;

  rotation_power_ += speed_.z * 0.005f * elapsed_time;

  // ボールの回転
  D3DXQUATERNION q;
  D3DXQuaternionRotationAxis(&q, &rotation_axis_, rotation_power_);
  D3DXMatrixRotationQuaternion(&rotation_matrix_, &q);

  ObjectFBXModel::SetRotationMatrix(rotation_matrix_);
  ObjectFBXModel::_Update(elapsed_time);
}
