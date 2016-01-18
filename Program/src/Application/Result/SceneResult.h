//==============================================================================
//
// SceneResult
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Scene/Scene.h"

#include "Framework/Object/root.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Alarm;
//class Root;
class HudNumber;
class Object2D;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneResult : public Scene {
public:
  // ctor
  SceneResult();

  // dtor
  virtual ~SceneResult();

  void SetYourScore(HudNumber* p_your_score) { p_hud_your_score_ = p_your_score; }
  void SetHighScore(HudNumber* p_high_score) { p_hud_high_score_ = p_high_score; }

  void Push_(ObjectBase* p_base) { p_root_->AttachChild(p_base); }

private:
  // _Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;
  // _Draw
  virtual void _Draw(void) override;

  // _setup alarm
  void _SetupAlarm(void);

  Root* p_root_;
  HudNumber* p_hud_high_score_;
  HudNumber* p_hud_your_score_;
  Object2D* p_jiji_;

  Alarm* p_alarm_;
  float sum_time_;
};
