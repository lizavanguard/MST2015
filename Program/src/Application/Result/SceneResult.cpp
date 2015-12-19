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
#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/SkyBox/SkyBox.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"

#include "window_config.h"

#include "Application/game_config.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/ScoreHolder/ScoreHolder.h"

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
  const D3DXVECTOR2 kYourScoreSize(400.0f, 200.0f);
  const D3DXVECTOR2 kHighScoreSize(kYourScoreSize * 0.7f);
  const float kMovingTime = 2.0f;
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
    , sum_time_(0.0f) {
  TextureManager::Instance().Load(kTextureGroupName);

  p_root_ = RootFactory::Create();

  p_hud_high_score_ = new HudNumber(kScorePlaceMax, kHighScoreStartPosition, kHighScoreSize);
  p_hud_high_score_->AssignNumber(ScoreHolderServiceLocator::Get()->GetHighScore());
  HudServiceLocator::Get()->PushAlphaHud(p_hud_high_score_);
  p_hud_your_score_ = new HudNumber(kScorePlaceMax, kYourScoreStartPosition, kYourScoreSize);
  p_hud_your_score_->AssignNumber(ScoreHolderServiceLocator::Get()->GetLatestScore());
  HudServiceLocator::Get()->PushAlphaHud(p_hud_your_score_);

  auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Result_grandfatherSlideIn", 640, 360);
  EffectManagerServiceLocator::Get()->SetScreenScale(h, 150, 100);

  SoundManager::Instance().PlayBGM(kBgmName);
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

  const float t = std::min<float>((sum_time_ / kMovingTime), 1.0f);

  D3DXVECTOR2 high_score_position = liza::math::InterpolateQuadraticEaseOut(t, kHighScoreStartPosition, kHighScoreEndPosition);
  p_hud_high_score_->UpdatePos(high_score_position);

  D3DXVECTOR2 your_score_position = liza::math::InterpolateQuadraticEaseOut(t, kYourScoreStartPosition, kYourScoreEndPosition);
  p_hud_your_score_->UpdatePos(your_score_position);

  p_root_->UpdateAll(elapsed_time);
  sum_time_ += elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneResult::_Draw(void) {
  p_root_->DrawAll();
}
