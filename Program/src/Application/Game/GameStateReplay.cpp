//==============================================================================
//
// GameStateReplay
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateReplay.h"
#include "GameStatePlayerInput.h"
#include "GameStateReady.h"
#include "ReplayListeners.h"
#include "GameMaster/GameMaster.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_control.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"

#include "Application/Alarm/Alarm.h"
#include "Application/game_config.h"
#include "Application/Player/Player.h"
#include "Application/Pin/PinManager.h"
#include "Application/ScoreHolder/ScoreHolder.h"
#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 10.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateReplay::GameStateReplay(SceneGame& scene_game)
    : GameState(scene_game)
    , p_alarm_(nullptr)
    , p_root_(nullptr)
    , ready_time_(kReadyTime)
    , is_skip_(false) {
  p_root_ = new Root();

  auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Game_blackOut", 640, 360);
  EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);

  _SetupAlarm();

  ready_time_ = kReadyTime;

  scene_game_.GetGameMaster().OnReplayMode();
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateReplay::~GameStateReplay() {
  SafeDelete(p_alarm_);
  SafeDelete(p_root_);
  scene_game_.GetGameMaster().OffReplayMode();
}

extern bool is_debug_throw_mode;
//------------------------------------------------
// Update
//------------------------------------------------
void GameStateReplay::Update(const float elapsed_time) {
  bool is_end = p_alarm_->Update(elapsed_time);

  if (is_end || is_skip_) {
    auto& game_master = scene_game_.GetGameMaster();
    if (!is_debug_throw_mode) {
      if (game_master.IsLastThrow()) {
        game_master.EndGame();
        ScoreHolderServiceLocator::Get()->AssignLatestScore(game_master.GetScoreSum());
        return;
      }
      game_master.GoToNextThrowing();
    }
    scene_game_.ChangeGameState(new GameStateReady(scene_game_, game_master.GetThrowCount()));
    scene_game_.Reset();
  }

  _Control();

  p_root_->UpdateAll(elapsed_time);

  if (p_alarm_->GetCurrentDataIndex() == 2) {
    auto& player = scene_game_.GetPlayer();
    if (player.GetPosition().z >= kGameEndZ) {
      p_alarm_->Jump(3);
      return;
    }
  }

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateReplay::Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _cotrol
//------------------------------------------------
void GameStateReplay::_Control(void) {
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  auto p_wii_controller = WiiControllerManager::Instance().GetWiiController(0);

  if (keyboard.IsTrigger(DIK_A)) {
    is_skip_ = true;
  }

#ifdef _DEBUG
  if (keyboard.IsTrigger(DIK_SPACE)) {
    auto& game_master = scene_game_.GetGameMaster();
    scene_game_.Reset();
    scene_game_.ChangeGameState(new GameStatePlayerInput(scene_game_));
  }
#endif
}

//------------------------------------------------
// _Setup Alarm
//------------------------------------------------
void GameStateReplay::_SetupAlarm(void) {
  // 1
  Alarm::DataContainerType data_container;
  Alarm::Data fading;
  fading.time = 1.5f;
  //fading.time = 0.1f;
  data_container.push_back(fading);

  // 2
  Alarm::Data reset;
  reset.time = 1.5f;
  //reset.time = 0.1f;
  reset.listener_list.push_back(new ResetListener(scene_game_, scene_game_.GetPlayer(), scene_game_.GetPinManager()));
  data_container.push_back(reset);

  // 3
  Alarm::Data shoot;
  shoot.time = 15.0f;
  shoot.listener_list.push_back(
      new ShootListener(scene_game_.GetPlayer(), scene_game_.GetPinManager(), scene_game_.GetGameMaster()));
  data_container.push_back(shoot);

  // 4
  Alarm::Data fade_out;
  fade_out.time = 1.3f;
  fade_out.listener_list.push_back(new FadeOutListener());
  data_container.push_back(fade_out);

  p_alarm_ = new Alarm(data_container);
}
