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
#include "Framework/Effect/EffectManager.h"
#include "Framework/Effect/EffectManagerServiceLocator.h"
#include "Framework/SkyBox/SkyBox.h"

#include "window_config.h"

#include "Application/Game/SceneGameFactory.h"
#include "Application/Player/Player.h"
#include "Application/Stage/Stage.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTextureGroupName = "Title";
  const char* kBgmName = "BGM_Title";

  const D3DXVECTOR3 kFixedCameraPosition(0.0f, 100.0f, -300.0f);
}

static bool s_is_ready = false;
static bool s_is_just_ready = false;
static EffectManager::Handle2D s_logo_handle(-1);

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneTitle::SceneTitle() : p_root_(nullptr) {
  TextureManager::Instance().Load(kTextureGroupName);

  p_root_ = RootFactory::Create();

  SkyBox* p_skybox = new SkyBox();
  p_root_->AttachChild(p_skybox);

  Stage* p_field = new Stage();
  p_root_->AttachChild(p_field);

  Player* p_player = new Player();
  p_root_->AttachChild(p_player);

  Camera& camera = CameraManager::Instance().Find("MAIN_1");
  camera.AssignCameraSteering(new CameraSteeringControl());

  Camera& camera2 = CameraManager::Instance().Find("MAIN_2");
  camera2._SetEye(kFixedCameraPosition);
  camera2.AssignCameraSteering(new CameraSteeringFixed(*p_player));

  SoundManager::Instance().PlayBGM(kBgmName);

  s_is_ready = false;
  s_is_just_ready = false;
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneTitle::~SceneTitle() {
  SoundManager::Instance().StopSound();

  EffectManagerServiceLocator::Get()->Stop2D(s_logo_handle);
  Camera& camera = CameraManager::Instance().Find("MAIN_1");
  camera.AssignCameraSteering(nullptr);

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

  //if (keyboard.IsTrigger(DIK_1)) {
  //  auto handle = EffectManagerServiceLocator::Get()->Play2D("EF_Title_fadeWhite", 640, 360);
  //  EffectManagerServiceLocator::Get()->SetScreenScale(handle, 50.0f, 50.0f);
  //  EffectManagerServiceLocator::Get()->SetRemovingCallbackFunction2D(handle, [](void) {
  //    s_is_just_ready = true;
  //  });
  //}

  //if (keyboard.IsTrigger(DIK_A)) {
  //  s_is_just_ready = true;
  //}

  //if (s_is_just_ready) {
  //  s_logo_handle = EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoFadeIn", 640, 360);
  //  EffectManagerServiceLocator::Get()->SetScreenScale(s_logo_handle, 50.0f, 50.0f);
  //  s_is_just_ready = false;
  //  s_is_ready = true;
  //}

  //if (s_is_ready) {
  //  if (keyboard.IsTrigger(DIK_SPACE)) {
  //    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  //  }
  //}

  //if (keyboard.IsTrigger(DIK_2)) {
  //  auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoSlideIn", 640, 360);
  //}

  p_root_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneTitle::_Draw(void) {
  p_root_->DrawAll();
}
