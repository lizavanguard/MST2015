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
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameStateReady : public SceneGame::GameState {
public:
  // ctor
  GameStateReady();

  // dtor
  virtual ~GameStateReady();

  // Update
  virtual void Update(float elapsed_time, GameState* p_next_state) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
  float ready_time_;
};
