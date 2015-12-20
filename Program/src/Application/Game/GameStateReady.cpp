//==============================================================================
//
// GameStateReady
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateReady.h"
#include "GameStatePlayerInput.h"
#include "GameMaster/GameMaster.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Camera/camera_steering_control.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"
#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Effect/EffectManager.h"

#include "Application/Player/Player.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 4.0f;
  const char* kThrowCountEffectName[] = {
    "EF_Game_firstThrowSign", "EF_Game_secondThrowSign"
  };
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateReady::GameStateReady(SceneGame& scene_game, const unsigned int throw_count)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  auto h = EffectManagerServiceLocator::Get()->Play2D(kThrowCountEffectName[throw_count], 640, 300);
  EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);

  // camera setting
  // HACK:
  auto& camera_manager = CameraManager::Instance();
  auto& camera1 = camera_manager.Find("MAIN_1");
  camera1._SetEye(D3DXVECTOR3(0.0f, 200.0, 0.0f));
  //camera1.AssignCameraSteering(new CameraSteeringHoming(scene_game_.GetPlayer(), 500, 300, 500));
  camera1.AssignCameraSteering(new CameraSteeringControl());
  auto& camera2 = camera_manager.Find("MAIN_2");
  static const float kEyeDistance = 200.0f;
  static const float kEyeHeight = 120.0f;
  static const float kAtDistance = 450.0f;
  camera2.AssignCameraSteering(new CameraSteeringHoming(scene_game_.GetPlayer(), kEyeDistance, kEyeHeight, kAtDistance));
  auto& camera3 = camera_manager.Find("MAIN_3");
  //camera3.AssignCameraSteering(new CameraSteeringFixed(scene_game_.GetPlayer()));
  camera3.AssignCameraSteering(new CameraSteeringHoming(scene_game_.GetPlayer(), 1000, 300, 500));

  camera_manager.SetMainCamera("MAIN_3");
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateReady::~GameStateReady() {
  //scene_game_.Detatch2D(p_root_);
  //Root::Destroy(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStateReady::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    scene_game_.ChangeGameState(new GameStatePlayerInput(scene_game_));
  }
  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateReady::Draw(void) {
}
