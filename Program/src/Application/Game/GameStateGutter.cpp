//==============================================================================
//
// GameStateGutter
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateGutter.h"
#include "GameStatePlayerInput.h"
#include "GameStateReady.h"
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
  const float kReadyTime = 4.0f;
  const float kFadeStartTime = 2.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateGutter::GameStateGutter(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime)
    , is_fading_out_(false)
    , h_gutter_(EffectManager::kNullHandle) {
  p_root_ = new Root();

  scene_game_.GetPlayer().MoveStop();
  scene_game_.OffBulletUpdate();

  h_gutter_ = EffectManagerServiceLocator::Get()->Play2D("EF_Game_gutter", 640, 360);
  EffectManagerServiceLocator::Get()->SetScreenScale(h_gutter_, 100, 100);

  ready_time_ = kReadyTime;
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateGutter::~GameStateGutter() {
  EffectManagerServiceLocator::Get()->Stop2D(h_gutter_);
  SafeDelete(p_root_);
}

extern bool is_debug_throw_mode;
//------------------------------------------------
// Update
//------------------------------------------------
void GameStateGutter::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
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

  if ((ready_time_ <= kFadeStartTime) && !is_fading_out_) {
    auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Game_blackOut", 640, 360);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);
    is_fading_out_ = true;
  }

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateGutter::Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _cotrol
//------------------------------------------------
void GameStateGutter::_Control(void) {
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