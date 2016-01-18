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
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"

#include "window_config.h"

#include "Application/game_config.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/ScoreHolder/ScoreHolder.h"

#include "Application/Alarm/Alarm.h"

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

  //p_hud_high_score_ = new HudNumber(kScorePlaceMax, kHighScoreStartPosition, kHighScoreSize);
  //p_hud_high_score_->AssignNumber(ScoreHolderServiceLocator::Get()->GetHighScore());
  //HudServiceLocator::Get()->PushAlphaHud(p_hud_high_score_);
  //p_hud_your_score_ = new HudNumber(kScorePlaceMax, kYourScoreStartPosition, kYourScoreSize);
  //p_hud_your_score_->AssignNumber(ScoreHolderServiceLocator::Get()->GetLatestScore());
  //HudServiceLocator::Get()->PushAlphaHud(p_hud_your_score_);

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
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
  }

  //if (sum_time_ >= kJijiSlideTime) {
  //  auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Result_scoreSlideIn", 640, 450);
  //  EffectManagerServiceLocator::Get()->SetScreenScale(h, 75, 60);

  //  //const float t = std::min<float>(((sum_time_ - kJijiSlideTime) / kMovingTime), 1.0f);
  //  //D3DXVECTOR2 high_score_position = liza::math::InterpolateQuadraticEaseOut(t, kHighScoreStartPosition, kHighScoreEndPosition);
  //  //p_hud_high_score_->UpdatePos(high_score_position);

  //  //D3DXVECTOR2 your_score_position = liza::math::InterpolateQuadraticEaseOut(t, kYourScoreStartPosition, kYourScoreEndPosition);
  //  //p_hud_your_score_->UpdatePos(your_score_position);
  //}
  p_alarm_->Update(elapsed_time);

  //if (p_hud_high_score_) {
  //  p_hud_high_score_->AddTime(elapsed_time);
  //}
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
  score_slide_in.time = 2.0f;
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
