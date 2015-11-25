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
    GameState(SceneGame& scene_game) : scene_game_(scene_game) {}
    virtual ~GameState() {}
    virtual void Update(float elapsed_time) = 0;
    virtual void Draw(void) = 0;

  protected:
    SceneGame& scene_game_;
  };

public:
  // ctor
  SceneGame();

  // dtor
  virtual ~SceneGame();

  // change game-state
  void ChangeGameState(GameState* p_game_state);

  void Reset(void);

  // HACK:
  Player& GetPlayer(void) const { return *p_player_; }
  PinManager& GetPinManager(void) const { return *p_pin_manager_; }

private:
  // Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;

  // Draw
  virtual void _Draw(void) override;

  GameState* p_game_state_;
  GameState* p_next_game_state_;
  CollisionManager* p_collision_manager_;

  Root* p_root_;
  Player* p_player_;
  PinManager* p_pin_manager_;
};
