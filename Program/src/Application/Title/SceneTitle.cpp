//==============================================================================
//
// SceneTitle
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneTitle.h"
#include "TitleListeners.h"

#include "Framework/AlphaObject/AlphaObjectManager.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/object_model.h"
#include "Framework/Object/root.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_control.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Camera/camera_steering_moving.h"
#include "Framework/Effect/EffectManager.h"
#include "Framework/Effect/EffectManagerServiceLocator.h"
#include "Framework/SkyBox/SkyBox.h"
#include "Framework/Hud/HudManager.h"

#include "window_config.h"

#include "Application/game_config.h"
#include "Application/Alarm/Alarm.h"
#include "Application/Game/SceneGameFactory.h"
#include "Application/Pin/BiggestPin.h"
#include "Application/Pin/PinConfig.h"
#include "Application/Pin/PinManager.h"
#include "Application/Player/Player.h"
#include "Application/Stage/Stage.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTextureGroupName = "Title";
  const char* kBgmName = "BGM_Title";

  const D3DXVECTOR3 kGameStartPosition(0.0f, 200.0f, -800.0f);
  const float kPinToStartTime = 5.0f;
  const float kStartWaitTime = 1.0f;
  const float kPlayerStartTime = 2.0f;
  const float kSideViewTime = 1.5f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneTitle::SceneTitle()
    : p_root_(nullptr)
    , p_player_(nullptr)
    , p_alarm_(nullptr)
    , sum_time_(0.0f) {
  TextureManager::Instance().Load(kTextureGroupName);

  p_root_ = RootFactory::Create();

  SkyBox* p_skybox = new SkyBox();
  p_root_->AttachChild(p_skybox);

  Stage* p_field = new Stage();
  p_root_->AttachChild(p_field);

  p_player_ = new Player();
  p_player_->SetPosition(kGameStartPosition);
  AlphaObjectServiceLocator::Get()->Push(p_player_);

  BiggestPin* p_biggest_pin = new BiggestPin(pin::biggest_pin::kTitlePosition);
  p_root_->AttachChild(p_biggest_pin);

  Camera& camera = CameraManager::Instance().Find("MAIN_1");
  camera.AssignCameraSteering(new CameraSteeringControl());

  Camera& camera2 = CameraManager::Instance().Find("MAIN_2");
  camera2.AssignCameraSteering(new CameraSteeringMoving(p_biggest_pin->GetPosition(), kGameStartPosition, kPinToStartTime));
  CameraManager::Instance().SetMainCameraUsingHandle(1);

  Camera& camera3 = CameraManager::Instance().Find("MAIN_3");
  auto p_homing = new CameraSteeringHoming(*p_player_, 5000.0f, 300.0f, 0.1f);
  p_homing->SetRotationY(D3DX_PI / 2);
  camera3.AssignCameraSteering(p_homing);

  _SetupAlarm();

  SoundManager::Instance().PlayBGM(kBgmName);
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneTitle::~SceneTitle() {
  SoundManager::Instance().StopSound();
  AlphaObjectServiceLocator::Get()->Clear();
  HudServiceLocator::Get()->Clear();
  Camera& camera = CameraManager::Instance().Find("MAIN_1");
  camera.AssignCameraSteering(nullptr);
  Camera& camera2 = CameraManager::Instance().Find("MAIN_2");
  camera2.AssignCameraSteering(nullptr);

  SafeDelete(p_alarm_);

  EffectManagerServiceLocator::Get()->Stop();

  Root::Destroy(p_root_);

  TextureManager::Instance().Unload(kTextureGroupName);
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneTitle::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  }

  bool is_movie_end = p_alarm_->Update(elapsed_time);

  if (!is_movie_end) {
    if (p_alarm_->GetCurrentDataIndex() >= 2) {
      p_player_->MoveForward();
    }

    if (p_alarm_->GetCurrentDataIndex() < 6) {
      if (keyboard.IsTrigger(DIK_1)) {
        p_alarm_->Jump(7);
      }
    }
  }

  else {
    if (keyboard.IsTrigger(DIK_1)) {
      p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
    }
  }

  //if (keyboard.IsTrigger(DIK_A)) {
  //  s_is_just_ready = true;
  //}

  //if (s_is_just_ready) {
  //  s_logo_handle = EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoFadeIn", 640, 360);
  //  EffectManagerServiceLocator::Get()->SetScreenScale(s_logo_handle, 50.0f, 50.0f);
  //  s_is_just_ready = false;
  //  s_is_ready = true;
  //}

  //oif (s_is_ready) {
  //  if (keyboard.IsTrigger(DIK_SPACE)) {
  //    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  //  }
  //}

  //if (keyboard.IsTrigger(DIK_2)) {
  //  auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoSlideIn", 640, 360);
  //}

  p_root_->UpdateAll(elapsed_time);
  sum_time_ += elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneTitle::_Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _Setup alarm
//------------------------------------------------
void SceneTitle::_SetupAlarm(void) {
  Alarm::DataContainerType data_container;

  // 1
  Alarm::Data pin_to_player;
  pin_to_player.time = kPinToStartTime;
  data_container.push_back(pin_to_player);

  // 2
  Alarm::Data start_wait;
  start_wait.time = kStartWaitTime;
  data_container.push_back(start_wait);

  // 3
  Alarm::Data player_start;
  player_start.time = kPlayerStartTime;
  player_start.listener_list.push_back(new PlayerStartListener(*p_player_));
  data_container.push_back(player_start);

  // 4
  Alarm::Data side_view;
  side_view.time = kSideViewTime;
  side_view.listener_list.push_back(new SideViewListener());
  data_container.push_back(side_view);

  // 5
  Alarm::Data audience_view;
  audience_view.time = 3.0f;
  audience_view.listener_list.push_back(new AudienceViewListener(*p_player_));
  data_container.push_back(audience_view);

  // 6
  Alarm::Data homing_view;
  homing_view.time = 1.5f;
  homing_view.listener_list.push_back(new HomingViewListener(*p_player_));
  data_container.push_back(homing_view);

  // 7
  Alarm::Data impact;
  impact.time = 1.0f;
  impact.listener_list.push_back(new ImpactListener());
  data_container.push_back(impact);

  // 8
  Alarm::Data dummy_end;
  dummy_end.listener_list.push_back(new DummyEndListener());
  data_container.push_back(dummy_end);

  p_alarm_ = new Alarm(data_container);
}
