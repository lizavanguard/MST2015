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
  GameStatePlayerInput();

  // dtor
  virtual ~GameStatePlayerInput();

  // Update
  virtual void Update(float elapsed_time, GameState* p_next_state) override;

  // Draw
  virtual void Draw(void) override;

private:
  Root* p_root_;
};
