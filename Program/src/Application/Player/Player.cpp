//==============================================================================
//
// Player
// Author: Shimizu Shoji
//
//==============================================================================
//struct {
//  handle;
//  target;
//
//  if (is_valid_handle)
//    location(target.position + offset);
//

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Player.h"
#include "PlayerBall.h"

#include "Framework/Object/object_fbx_model.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 200.0f;

  const float kMovingSpeed = 30.0f;

  const float kAdjustedValueRotationToPower = 1000.0f;
  //const float kCurveReaction = 0.025f;
  const float kCurveReaction = 0.025f;
  const float kShotSpeed = 5000.0f;

  const Vector3 kStartPosition(0.0f, 200.0f, -100.0f);
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player()
    : CollisionObject(kSize)
    , is_shot_(false)
    , adjusted_value_(kAdjustedValueRotationToPower)
    , curve_reaction_(kCurveReaction)
    , shot_speed_(kShotSpeed)
    , moving_speed_(kMovingSpeed)
    , p_ball_(nullptr)
    , h_wind_effect_(-1) {
  AttachChild(new ObjectFBXModel("humanG_07.fbx"));
  AttachChild(new ObjectModel("ballObj_03"));
  p_ball_ = new PlayerBall();
  AttachChild(p_ball_);
  Reset();
}

//------------------------------------------------
// dtor
//------------------------------------------------
Player::~Player() {
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);
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

  p_ball_->Shoot(rotation);

  is_shot_ = true;

  h_wind_effect_ = EffectManagerServiceLocator::Get()->Play3D("EF_Ball_Wind", position_.x, position_.y, position_.x + 100);
  EffectManagerServiceLocator::Get()->SetRotation(h_wind_effect_, D3DXVECTOR3(0, 1, 0), D3DX_PI);
  EffectManagerServiceLocator::Get()->SetScale(h_wind_effect_, 100, 100, 100);
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Player::Reset(void) {
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);

  is_shot_ = false;
  position_ = kStartPosition;
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  p_ball_->Reset();
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
  static const float kSpeed = 100.0f;
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

  static const float kRotationFixedValue = 0.005f;
  p_ball_->AddRotationPower(speed_.z * elapsed_time * kRotationFixedValue);

  EffectManagerServiceLocator::Get()->SetPosition(h_wind_effect_, position_.x, position_.y, position_.z);
}
