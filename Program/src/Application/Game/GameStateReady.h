//==============================================================================
//
// GameStateReady
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Game/SceneGame.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class delcaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Controller;
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameStateReady : public SceneGame::GameState {
public:
  // ctor
  GameStateReady(SceneGame& scene_game);

  // dtor
  virtual ~GameStateReady();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
  Controller* p_controller_;
  float ready_time_;
};
