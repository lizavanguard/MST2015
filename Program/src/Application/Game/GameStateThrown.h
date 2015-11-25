//==============================================================================
//
// GameStateThrown
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
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameStateThrown : public SceneGame::GameState {
public:
  // ctor
  GameStateThrown(SceneGame& scene_game);

  // dtor
  virtual ~GameStateThrown();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
  float ready_time_;
};
