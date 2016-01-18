//==============================================================================
//
// GameStateEndZ
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateEndZ.h"
#include "GameStatePlayerInput.h"
#include "GameStateReplay.h"
#include "GameMaster/GameMaster.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"

#include "Application/game_config.h"
#include "Application/Player/Player.h"
#include "Application/ScoreHolder/ScoreHolder.h"
#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 0.8f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateEndZ::GameStateEndZ(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  p_root_ = new Root();

  ready_time_ = kReadyTime;
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateEndZ::~GameStateEndZ() {
  SafeDelete(p_root_);
}

extern bool is_debug_throw_mode;
//------------------------------------------------
// Update
//------------------------------------------------
void GameStateEndZ::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    auto& game_master = scene_game_.GetGameMaster();
    game_master.CalculateScore();
    scene_game_.ChangeGameState(new GameStateReplay(scene_game_));
  }

  _Control();
  scene_game_.GetPlayer().Brake();

  p_root_->UpdateAll(elapsed_time);

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateEndZ::Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _cotrol
//------------------------------------------------
void GameStateEndZ::_Control(void) {
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  auto p_wii_controller = WiiControllerManager::Instance().GetWiiController(0);

#ifdef _DEBUG
  if (keyboard.IsTrigger(DIK_SPACE)) {
    auto& game_master = scene_game_.GetGameMaster();
    scene_game_.Reset();
    scene_game_.ChangeGameState(new GameStatePlayerInput(scene_game_));
  }
#endif
}