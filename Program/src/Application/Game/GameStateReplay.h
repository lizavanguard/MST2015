//==============================================================================
//
// GameStateReplay
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Game/SceneGame.h"
#include "Framework/Effect/EffectManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class delcaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Alarm;
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameStateReplay : public SceneGame::GameState {
public:
  // ctor
  GameStateReplay(SceneGame& scene_game);

  // dtor
  virtual ~GameStateReplay();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  // _cotrol
  void _Control(void);
  void _SetupAlarm(void);

  // property
  Root* p_root_;
  float ready_time_;
  Alarm* p_alarm_;
  bool is_skip_;
};
