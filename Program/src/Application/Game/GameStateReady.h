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
  GameStateReady(SceneGame& scene_game, unsigned int throw_count);

  // dtor
  virtual ~GameStateReady();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
  float ready_time_;
};
