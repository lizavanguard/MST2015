//==============================================================================
//
// ResultListeners
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Alarm/Alarm.h"
#include "Application/Player/Player.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"

#include "Application/Result/SceneResult.h"
#include "Application/game_config.h"
#include "window_config.h"

#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Application/ScoreHolder/ScoreHolder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const D3DXVECTOR2 kYourScoreSize(350.0f, 180.0f);
  const D3DXVECTOR2 kHighScoreSize(kYourScoreSize * 0.7f);
}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ScoreSlideListener : public Alarm::Listener {
public:
  // ctor/dtor
  ScoreSlideListener() {}
  virtual ~ScoreSlideListener() {}

  // Notify
  virtual void Notify(void) override {
    auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Result_scoreSlideIn", 640, 450);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 80, 45);
  }
};

class YourScoreShowListener : public Alarm::Listener {
public:
  // ctor/dtor
  YourScoreShowListener(SceneResult* p_result) : p_result_(p_result) {}
  virtual ~YourScoreShowListener() {}

  // Notify
  virtual void Notify(void) override {
    auto* p = new HudNumber(kScorePlaceMax, D3DXVECTOR2(kWindowWidthF * 0.5f, 450.0f), kYourScoreSize);
    p->AssignNumber(ScoreHolderServiceLocator::Get()->GetLatestScore());
    HudServiceLocator::Get()->PushAlphaHud(p);
    p_result_->SetYourScore(p);
  }

private:
  SceneResult* p_result_;
};

class ScoreFadeListener : public Alarm::Listener {
public:
  // ctor/dtor
  ScoreFadeListener(SceneResult* p_result) : p_result_(p_result) {}
  virtual ~ScoreFadeListener() {}

  // Notify
  virtual void Notify(void) override {
    p_result_->Push_(
      new Object2D("Result/EF_result_scoreFlash",
      D3DXVECTOR3(640.0f, 240.0f, 0.0f), kHighScoreSize,
      new Object2DSteeringFlashing(2.0f)));
    //auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Result_scoreFlash", 640, 200);
    //EffectManagerServiceLocator::Get()->SetScreenScale(h, 80, 45);
  }

private:
  SceneResult* p_result_;
};

class ScoreShowListener : public Alarm::Listener {
public:
  // ctor/dtor
  ScoreShowListener(SceneResult* p_result) : p_result_(p_result) {}
  virtual ~ScoreShowListener() {}

  // Notify
  virtual void Notify(void) override {
    auto* p = new HudNumber(kScorePlaceMax, D3DXVECTOR2(kWindowWidthF * 0.5f, 200.0f), kHighScoreSize);
    p->AssignNumber(ScoreHolderServiceLocator::Get()->GetHighScore());
    p->SetInterval(1.0f);
    HudServiceLocator::Get()->PushAlphaHud(p);
    p_result_->SetHighScore(p);
  }

private:
  SceneResult* p_result_;
};
