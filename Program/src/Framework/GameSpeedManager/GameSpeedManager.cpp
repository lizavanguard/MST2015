//==============================================================================
//
// GameSpeedManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameSpeedManager.h"

#include "Framework/DebugProc/DebugProc.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameSpeedManager::GameSpeedManager()
    : speed_rate_(1.0f)
    , latest_elapsed_time_(0.0f)
    , latest_raw_elapsed_time_(0.0f) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameSpeedManager::~GameSpeedManager() {
}

//------------------------------------------------
// Update
// return = elapsed_time * game_speed_rate
//------------------------------------------------
float GameSpeedManager::Update(const float elapsed_time) {
  latest_elapsed_time_ = elapsed_time * speed_rate_;
  latest_raw_elapsed_time_ = elapsed_time;

  _DebugControlSpeed();

  return latest_elapsed_time_;
}

//------------------------------------------------
// _Check valid speed
//------------------------------------------------
void GameSpeedManager::_CheckSpeed(void) {
  MY_BREAK_ASSERT(speed_rate_ > 0.0f);
}

//------------------------------------------------
// 
//------------------------------------------------
void GameSpeedManager::_DebugControlSpeed(void) {
#ifdef _DEBUG

  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeedRateChangeSpeed = 0.01f;

  if (keyboard.IsPress(DIK_F1)) {
    speed_rate_ += kSpeedRateChangeSpeed;
  }
  if (keyboard.IsPress(DIK_F2)) {
    speed_rate_ -= kSpeedRateChangeSpeed;
    speed_rate_ = std::max<float>(speed_rate_, 0.00001f);
  }

  DebugProc::Print("現在のゲーム進行速度[%.3f]\n", speed_rate_);
  DebugProc::Print("速度上昇[F1], 速度減少[F2]\n");

#endif
}
