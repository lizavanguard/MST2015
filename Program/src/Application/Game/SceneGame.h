//==============================================================================
//
// SceneGame
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Scene/Scene.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class delcaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CollisionManager;
class Controller;
class Player;
class PinManager;
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneGame : public Scene {
public:
  // interface
  class GameState {
  public:
    virtual ~GameState() {}
    virtual void Update(float elapsed_time, GameState* p_next_state) = 0;
    virtual void Draw(void) = 0;
  };

public:
  // ctor
  SceneGame();

  // dtor
  virtual ~SceneGame();

  // change controller
  void ChangeController(Controller* p_controller);

private:
  // Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;

  // Draw
  virtual void _Draw(void) override;

  GameState* p_game_state_;
  Controller* p_controller_;
  CollisionManager* p_collision_manager_;

  Root* p_root_;
  Player* p_player_;
  PinManager* p_pin_manager_;
};
