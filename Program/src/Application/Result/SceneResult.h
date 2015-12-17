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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Root;
class HudNumber;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneResult : public Scene {
public:
  // ctor
  SceneResult();

  // dtor
  virtual ~SceneResult();

private:
  // _Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;
  // _Draw
  virtual void _Draw(void) override;

  Root* p_root_;
  HudNumber* p_hud_high_score_;
  HudNumber* p_hud_your_score_;
  float sum_time_;
};
