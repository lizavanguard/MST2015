//==============================================================================
//
// SceneResult
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneResult.h"
#include "ResultListeners.h"

#include "liza/math/Interpolation.hpp"

#include "Framework/AlphaObject/AlphaObjectManager.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Effect/EffectManager.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/object_model.h"
#include "Framework/Object/root.h"
#include "Framework/Object/Hud/HudOverlay/HudOverlay.h"
#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/SkyBox/SkyBox.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"
#include "Framework/Steering/Object2D/Object2DSteeringMoving.h"
#include "Framework/Steering/Object2D/Object2DSteeringUVUpdating.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"

#include "window_config.h"

#include "Application/game_config.h"
#include "Application/Alarm/Alarm.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/ScoreHolder/ScoreHolder.h"
#include "Application/WiiController/WiiControllerManager.h"
#include "Application/WiiController/CWiiController.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTextureGroupName = "Result";
  const char* kBgmName = "BGM_Result";

  const float kX = 640.0f;
  const D3DXVECTOR2 kYourScoreStartPosition(kX, -1000.0f);
  const D3DXVECTOR2 kYourScoreEndPosition(kX,    400.0f);
  const D3DXVECTOR2 kHighScoreStartPosition(kYourScoreStartPosition.x, kYourScoreStartPosition.y + 150.0f);
  const D3DXVECTOR2 kHighScoreEndPosition(kYourScoreEndPosition.x, kYourScoreEndPosition.y - 250.0f);
  //const D3DXVECTOR2 kYourScoreSize(400.0f, 200.0f);
  //const D3DXVECTOR2 kHighScoreSize(kYourScoreSize * 0.7f);
  const float kMovingTime = 2.0f;

  const float kJijiSlideTime = 3.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneResult::SceneResult()
    : p_root_(nullptr)
    , p_hud_high_score_(nullptr)
    , p_hud_your_score_(nullptr)
    , p_jiji_(nullptr)
    , p_alarm_(nullptr)
    , sum_time_(0.0f) {
  TextureManager::Instance().Load(kTextureGroupName);

  p_root_ = RootFactory::Create();

  //auto p_uv_updating = new Object2DSteeringUVUpdating(0.1f, .0f);
  auto p_uv_updating = new Object2DSteeringUVUpdating(0.25f, -0.2f);
  auto p_bg = new Object2D("Result/EF_result_fanfare", D3DXVECTOR3(kWindowWidthF * 0.5f, kWindowHeightF *0.5f, 0.0f),
    D3DXVECTOR2(kWindowWidthF, kWindowHeightF), p_uv_updating);
  p_root_->AttachChild(p_bg);

  auto p_moving = new Object2DSteeringMoving(
    D3DXVECTOR3(kWindowWidthF * 0.5f, kWindowHeightF + 1280.0f, 0.0f),
    D3DXVECTOR3(kWindowWidthF * 0.5f, kWindowHeightF * 0.5f - 1.0f, 0.0f), kJijiSlideTime);
  p_jiji_ = new Object2D("Result/EF_result_grandfatherSlideIn_0", D3DXVECTOR3(kWindowWidthF * 0.5f, kWindowHeightF * 0.5f, 0.0f), D3DXVECTOR2(kWindowWidthF, kWindowHeightF), p_moving);
  p_root_->AttachChild(p_jiji_);

  SoundManager::Instance().PlayBGM(kBgmName);

  _SetupAlarm();
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneResult::~SceneResult() {
  SoundManager::Instance().StopSound();
  AlphaObjectServiceLocator::Get()->Clear();
  HudServiceLocator::Get()->Clear();
  EffectManagerServiceLocator::Get()->Stop();

  Root::Destroy(p_root_);

  SafeDelete(p_alarm_);

  TextureManager::Instance().Unload(kTextureGroupName);
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneResult::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  const auto& remocon = WiiControllerManager::Instance().GetWiiController(0);
  if (keyboard.IsTrigger(DIK_RETURN) || (remocon?remocon->getTrigger(WC_A):false)) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
  }

  p_alarm_->Update(elapsed_time);

  p_root_->UpdateAll(elapsed_time);
  sum_time_ += elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneResult::_Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// _setup alarm
//------------------------------------------------
void SceneResult::_SetupAlarm(void) {
  Alarm::DataContainerType data_container;

  // 1
  Alarm::Data jiji_slide_in;
  jiji_slide_in.time = kJijiSlideTime;
  data_container.push_back(jiji_slide_in);

  Alarm::Data score_slide_in;
  score_slide_in.time = 2.2f;
  score_slide_in.listener_list.push_back(new ScoreSlideListener());
  data_container.push_back(score_slide_in);

  Alarm::Data your_score_show;
  your_score_show.listener_list.push_back(new YourScoreShowListener(this));
  your_score_show.time = 2.0f;
  data_container.push_back(your_score_show);

  Alarm::Data high_score_fade_in;
  high_score_fade_in.time = 0.0f;
  high_score_fade_in.listener_list.push_back(new ScoreFadeListener(this));
  data_container.push_back(high_score_fade_in);

  Alarm::Data score_show;
  score_show.listener_list.push_back(new ScoreShowListener(this));
  score_show.time = 2.0f;
  data_container.push_back(score_show);

  p_alarm_ = new Alarm(data_container);
}
