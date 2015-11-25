//==============================================================================
//
// SceneGame
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneGame.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/root.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/SkyBox/SkyBox.h"

#include "Application/Controller/Controller.h"
#include "Application/Collision/CollisionManager.h"
#include "Application/Game/GameStateReady.h"
#include "Application/Player/Player.h"
#include "Application/Pin/PinManager.h"
#include "Application/Title/SceneTitleFactory.h"


// HACK:
#include "Application/Test/Test.h"
Test* g_p_test = nullptr;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
    : p_game_state_(nullptr)
    , p_controller_(nullptr)
    , p_collision_manager_(nullptr)
    , p_root_(nullptr)
    , p_player_(nullptr)
    , p_pin_manager_(nullptr) {
  // game state
  p_game_state_ = new GameStateReady();

  // camera
  static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 75.0f, -40.0f};
  //static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 10.0f, -40.0f};
  auto camera = CameraFactory::Create(kInitialEyePosition, D3DXVECTOR3(0, 0, 0));
  CameraManager::Instance().Register("MAIN_CAMERA", camera);

  // object
  p_root_ = RootFactory::Create();
  p_player_ = PlayerFactory::Create();
  p_root_->AttachChild(p_player_);
  p_pin_manager_ = PinManagerFactory::Create();
  p_root_->AttachChild(p_pin_manager_);

  p_root_->AttachChild(SkyBoxFactory::Create());
  p_root_->AttachChild(ObjectModelFactory::Create("field"));

  // collision
  p_collision_manager_ = new CollisionManager(*p_player_, *p_pin_manager_);

  // controller
  p_controller_ = new Controller();

  // camera setting
  //camera->AssignCameraSteering(new CameraSteeringFixed(*player));
  camera->AssignCameraSteering(new CameraSteeringHoming(*p_player_));
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  SafeDelete(p_controller_);
  CameraManager::Instance().UnRegister();
  SafeDelete(p_collision_manager_);
  Root::Destroy(p_root_);
  SafeDelete(p_game_state_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneGame::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  // game-state
  GameState* p_next_state = nullptr;
  p_game_state_->Update(elapsed_time, p_next_state);

  if (p_next_state) {
    SafeDelete(p_game_state_);
    p_game_state_ = p_next_state;
  }

  p_controller_->Update(*p_player_, *p_pin_manager_);

  p_root_->UpdateAll(elapsed_time);

  p_collision_manager_->Update();


#ifdef _DEBUG
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
  }
#endif
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::_Draw(void) {
  p_game_state_->Draw();
  p_root_->DrawAll();
}
