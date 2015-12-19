//==============================================================================
//
// GameStateThrown
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateThrown.h"
#include "GameStateReady.h"
#include "GameMaster/GameMaster.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"

#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 15.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateThrown::GameStateThrown(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  p_root_ = new Root();
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateThrown::~GameStateThrown() {
  auto camera_steering = static_cast<CameraSteeringHoming*>(CameraManager::Instance().Find("MAIN_2").GetCameraSteering());
  camera_steering->SetRotationY(0.0f);
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStateThrown::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    auto& game_master = scene_game_.GetGameMaster();
    if (game_master.IsLastThrow()) {
      game_master.EndGame();
      return;
    }
    game_master.GoToNextThrowing();
    scene_game_.ChangeGameState(new GameStateReady(scene_game_, game_master.GetThrowCount()));
    scene_game_.Reset();
  }

  _Control();

  p_root_->UpdateAll(elapsed_time);

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateThrown::Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _cotrol
//------------------------------------------------
void GameStateThrown::_Control(void) {
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  auto p_wii_controller = WiiControllerManager::Instance().GetWiiController(0);

  const bool is_key_rotated_left = keyboard.IsPress(DIK_LEFT);
  const bool is_wii_rotated_left = p_wii_controller ? p_wii_controller->getPress(WC_LEFT) : false;
  const bool is_rotated_left = is_key_rotated_left || is_wii_rotated_left;
  if (is_rotated_left) {
    auto camera_steering = static_cast<CameraSteeringHoming*>(CameraManager::Instance().Find("MAIN_2").GetCameraSteering());
    camera_steering->RotateLeft();
  }

  const bool is_key_rotated_right = keyboard.IsPress(DIK_RIGHT);
  const bool is_wii_rotated_right = p_wii_controller ? p_wii_controller->getPress(WC_RIGHT) : false;
  const bool is_rotated_right = is_key_rotated_right || is_wii_rotated_right;
  if (is_rotated_right) {
    auto camera_steering = static_cast<CameraSteeringHoming*>(CameraManager::Instance().Find("MAIN_2").GetCameraSteering());
    camera_steering->RotateRight();
  }
}