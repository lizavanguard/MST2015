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
  static const float kSize = 3.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player()
    : ObjectModel(kModelname), CollisionObject(kSize) {
  Reset();
}

//------------------------------------------------
// dtor
//------------------------------------------------
Player::~Player() {
}

//------------------------------------------------
// Shoot
//------------------------------------------------
void Player::Shoot(const D3DXVECTOR3&) {
  static const float kShootPower = 10.0f * 0.016666f;
  velocity_.z += kShootPower;
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Player::Reset(void) {
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
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeed = 1.0f;
  const float true_speed = kSpeed * elapsed_time;

  if (keyboard.IsPress(DIK_W)) {
    velocity_.z += true_speed;
  }
  if (keyboard.IsPress(DIK_S)) {
    velocity_.z -= true_speed;
  }
  if (keyboard.IsPress(DIK_A)) {
    velocity_.x -= true_speed;
  }
  if (keyboard.IsPress(DIK_D)) {
    velocity_.x += true_speed;
  }
  if (keyboard.IsPress(DIK_RETURN)) {
    Shoot(D3DXVECTOR3());
  }
  if (keyboard.IsPress(DIK_SPACE)) {
    Reset();
  }

  velocity_ *= 0.998f;
  position_ += velocity_;
}
