//==============================================================================
//
// GameStatePlayerInput
// Author: Shimizu Shoji
//
// MEMO: UIÉgÉJÅH
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
class GameStatePlayerInput : public SceneGame::GameState {
public:
  // ctor
  GameStatePlayerInput(SceneGame& scene_game);

  // dtor
  virtual ~GameStatePlayerInput();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
};
