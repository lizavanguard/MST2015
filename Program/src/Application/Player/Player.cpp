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
  const char* kModelname = "ball";
  const float kSize = 3.0f;

  const float kMovingSpeed = 0.3f;

  const float kAdjustedValueRotationToPower = 15.0f;
  const float kCurveReaction = 0.025f;
  const float kShotSpeed = 100.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player()
    : ObjectModel(kModelname)
    , CollisionObject(kSize)
    , is_shot_(false)
    , speed_(0.0f, 0.0f, 0.0f)
    , adjusted_value_(kAdjustedValueRotationToPower)
    , curve_reaction_(kCurveReaction)
    , shot_speed_(kShotSpeed)
    , moving_speed_(kMovingSpeed) {
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
  position_.x -= moving_speed_;
}

void Player::MoveRight(void) {
  position_.x += moving_speed_;
}

//------------------------------------------------
// Shoot
//------------------------------------------------
void Player::Shoot(const float rotation) {
  if (is_shot_) {
    return;
  }

  speed_.z += shot_speed_;

  const float true_power = rotation * adjusted_value_;
  speed_.x = true_power;
  velocity_.x -= true_power * curve_reaction_;

  is_shot_ = true;
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Player::Reset(void) {
  is_shot_ = false;
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  position_ = D3DXVECTOR3(0.0f, 0.0f, -30.0f);
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
  static float shot_rotation = 0.0f;

  if (keyboard.IsPress(DIK_W)) {
    speed_.z += true_speed;
  }
  if (keyboard.IsPress(DIK_S)) {
    speed_.z -= true_speed;
  }
  if (keyboard.IsPress(DIK_A)) {
    MoveLeft();
  }
  if (keyboard.IsPress(DIK_D)) {
    MoveRight();
  }
  if (keyboard.IsPress(DIK_LCONTROL)) {
    Shoot(shot_rotation);
  }
  if (keyboard.IsPress(DIK_SPACE)) {
    Reset();
  }

  if (keyboard.IsPress(DIK_I)) {
    speed_.y += true_speed;
  }
  if (keyboard.IsPress(DIK_K)) {
    speed_.y -= true_speed;
  }

  if (keyboard.IsPress(DIK_1)) { shot_rotation += 0.01f; }
  if (keyboard.IsPress(DIK_2)) { shot_rotation -= 0.01f; }
  if (keyboard.IsPress(DIK_3)) { curve_reaction_+= 0.0003f; }
  if (keyboard.IsPress(DIK_4)) { curve_reaction_ -= 0.0003f; }
  if (keyboard.IsPress(DIK_5)) { shot_speed_ += 0.1f; }
  if (keyboard.IsPress(DIK_6)) { shot_speed_ -= 0.1f; }
  if (keyboard.IsPress(DIK_7)) { adjusted_value_ += 0.1f; }
  if (keyboard.IsPress(DIK_8)) { adjusted_value_ -= 0.1f; }

  DebugProc::Print("éÀèoéûâÒì]ó :[%.3f]\nã»Ç™ÇËï˚:[%.3f]\néÀèoóÕ:[%.3f]\nã»Ç™ÇËï˚ÇÃí≤êÆíl:[%.3f]\n", shot_rotation, curve_reaction_, shot_speed_, adjusted_value_);

#endif

  velocity_ *= 0.998f;
  speed_ += velocity_;
  speed_ *= 0.998f;
  position_ += speed_ * elapsed_time;
}
