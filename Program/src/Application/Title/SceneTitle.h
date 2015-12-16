//==============================================================================
//
// SceneTitle
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
class Alarm;
class Player;
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneTitle : public Scene {
public:
  // ctor
  SceneTitle();

  // dtor
  virtual ~SceneTitle();

private:
  // Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;
  // Draw
  virtual void _Draw(void) override;

  // _function
  void _SetupAlarm(void);

  Root* p_root_;
  Player* p_player_;
  Alarm* p_alarm_;
  float sum_time_;
};
