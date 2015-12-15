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

#include "Framework/AlphaObject/AlphaObjectManager.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_config.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Camera/camera_steering_control.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/object_fbx_model.h"
#include "Framework/Object/root.h"
#include "Framework/Object/object_model.h"
#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/SkyBox/SkyBox.h"

#include "Application/Collision/CollisionManager.h"
#include "Application/Game/GameStateReady.h"
#include "Application/Game/GameMaster/GameMaster.h"
#include "Application/Player/Player.h"
#include "Application/Pin/PinManager.h"
#include "Application/Stage/Stage.h"
#include "Application/Title/SceneTitleFactory.h"

#include "Framework/Effect/EffectManager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
    : p_game_state_(nullptr)
    , p_next_game_state_(nullptr)
    , p_collision_manager_(nullptr)
    , p_game_master_(nullptr)
    , p_2d_root_(nullptr)
    , p_3d_root_(nullptr)
    , p_player_(nullptr)
    , p_pin_manager_(nullptr)
    , p_hud_number_(nullptr) {
  TextureManager::Instance().Load("Game");

  p_2d_root_ = RootFactory::Create();
  p_3d_root_ = RootFactory::Create();

  // game state
  p_game_state_ = new GameStateReady(*this, 0);

  // object
  auto p_skybox = SkyBoxFactory::Create();
  p_skybox->OnAllDrawed();
  p_3d_root_->AttachChild(p_skybox);

  p_pin_manager_ = PinManagerFactory::Create();
  p_3d_root_->AttachChild(p_pin_manager_);
  auto p_field = new Stage();
  p_3d_root_->AttachChild(p_field);

  // Player ‚ð 3Dƒ‚ƒfƒ‹‚Ì’†‚Å‚Íˆê”ÔÅŒã‚É•`‰æ‚·‚é‚±‚Æ
  p_player_ = PlayerFactory::Create();
  AlphaObjectServiceLocator::Get()->Push(p_player_);

  p_hud_number_ = new HudNumber(3, Vector2(100, 100), Vector2(50, 50));
  p_2d_root_->AttachChild(p_hud_number_);
  HudServiceLocator::Get()->Push(p_2d_root_);

  // collision
  p_collision_manager_ = new CollisionManager(*p_player_, *p_pin_manager_);

  // game master
  p_game_master_ = new GameMaster(*p_hud_number_, *p_pin_manager_, *p_collision_manager_);

  // camera setting
  // HACK:
  auto& camera_manager = CameraManager::Instance();
  auto& camera1 = camera_manager.Find("MAIN_1");
  camera1.AssignCameraSteering(new CameraSteeringControl());
  auto& camera2 = camera_manager.Find("MAIN_2");
  static const float kEyeDistance = 10.0f;
  static const float kEyeHeight = 75.0f;
  static const float kAtDistance = 450.0f;
  camera2.AssignCameraSteering(new CameraSteeringHoming(*p_player_, kEyeDistance, kEyeHeight, kAtDistance));
  auto& camera3 = camera_manager.Find("MAIN_3");
  camera3.AssignCameraSteering(new CameraSteeringFixed(*p_player_));
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  TextureManager::Instance().Unload("Game");

  HudServiceLocator::Get()->Clear();
  AlphaObjectServiceLocator::Get()->Clear();
  SafeDelete(p_game_state_);

  auto& camera_manager = CameraManager::Instance();
  for (int i = 0; i < kCameraMax; ++i) {
    auto& camera = camera_manager.FindUsingHandle(i);
    camera.AssignCameraSteering(nullptr);
  }
  camera_manager.SetMainCameraUsingHandle(0);

  SafeDelete(p_game_master_);
  SafeDelete(p_collision_manager_);
  SafeDelete(p_next_game_state_);
  Root::Destroy(p_3d_root_);
}

//------------------------------------------------
// change game-state
//------------------------------------------------
void SceneGame::ChangeGameState(GameState* p_game_state) {
  p_next_game_state_ = p_game_state;
}

//------------------------------------------------
// reset
//------------------------------------------------
void SceneGame::Reset(void) {
  p_player_->Reset();
  p_pin_manager_->Reset();
}

//------------------------------------------------
// HACK:
// Attach/Detach
//------------------------------------------------
void SceneGame::Attach2D(ObjectBase* p_object) { p_2d_root_->AttachChild(p_object); }
void SceneGame::Detatch2D(ObjectBase* p_object) { p_2d_root_->DetachChild(p_object); }

//------------------------------------------------
// Update
//------------------------------------------------
void SceneGame::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  if (p_game_master_->IsEndGame()) {
    return;
  }

  p_game_state_->Update(elapsed_time);
  if (p_game_master_->IsEndGame()) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
    return;
  }

  if (p_next_game_state_) {
    SafeDelete(p_game_state_);
    p_game_state_ = p_next_game_state_;
    p_next_game_state_ = nullptr;
  }

  p_3d_root_->UpdateAll(elapsed_time);
  p_2d_root_->UpdateAll(elapsed_time);

  p_collision_manager_->Update();

  p_game_master_->Update(elapsed_time);

#ifdef _DEBUG
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
    return;
  }

  if (keyboard.IsTrigger(DIK_1)) {
    CameraManager::Instance().SetMainCamera("MAIN_1");
  }
  if (keyboard.IsTrigger(DIK_2)) {
    CameraManager::Instance().SetMainCamera("MAIN_2");
  }
  if (keyboard.IsTrigger(DIK_3)) {
    CameraManager::Instance().SetMainCamera("MAIN_3");
  }
  if (keyboard.IsTrigger(DIK_7)) {
    auto h = EffectManagerServiceLocator::Get()->Play3D("EF_Game_ballWind", 0, 0, 0);
    EffectManagerServiceLocator::Get()->SetScale(h, 50, 50, 50);
  }
  if (keyboard.IsTrigger(DIK_8)) {
    EffectManagerServiceLocator::Get()->Play3D("SE_test_off_x100", 0, 0, 0);
  }
  if (keyboard.IsTrigger(DIK_9)) {
    auto h = EffectManagerServiceLocator::Get()->Play3D("ef_pin_sita", 0, 10, 0);
    EffectManagerServiceLocator::Get()->SetScale(h, 2.0f, 2.0f, 2.0f);
  }

  static EffectManager::Handle2D h;
  if (keyboard.IsTrigger(DIK_0)) {
    EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoPinParticle", 640, 360);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 50.0f, 50.0f);
    EffectManagerServiceLocator::Get()->SetRemovingCallbackFunction2D(h, [](){
      auto handle = EffectManagerServiceLocator::Get()->Play2D("EF_Title_slideIn", 640, 360);
      EffectManagerServiceLocator::Get()->SetScreenScale(handle, 50.0f, 50.0f);
    });
  }
  if (keyboard.IsTrigger(DIK_BACKSPACE)) {
    EffectManagerServiceLocator::Get()->Stop2D(h);
  }

  if (keyboard.IsTrigger(DIK_YEN)) {
    static bool is_wireframe = true;
    DeviceHolder::Instance().GetDevice()->SetRenderState(D3DRS_FILLMODE, is_wireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
    is_wireframe = !is_wireframe;
  }
#endif

}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::_Draw(void) {
  p_game_state_->Draw();
  p_3d_root_->DrawAll();
 // p_2d_root_->DrawAll();
}
