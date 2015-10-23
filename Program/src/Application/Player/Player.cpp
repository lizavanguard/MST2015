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
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player()
    : ObjectModel(kModelname) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Player::~Player() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Player::_Update(const float elapsed_time) {
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeed = 0.7f;
  const float true_speed = kSpeed * elapsed_time;

  if (keyboard.IsPress(DIK_W)) {
    velocity_.z += true_speed;
  }
  if (keyboard.IsPress(DIK_S)) {
    velocity_.z -= true_speed;
  }
  if (keyboard.IsPress(DIK_A)) {
    velocity_.x += true_speed;
  }
  if (keyboard.IsPress(DIK_W)) {
    velocity_.x -= true_speed;
  }

  velocity_ *= 0.099f;
  position_ += velocity_;
}
