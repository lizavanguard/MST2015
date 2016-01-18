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
class BulletManager;
class CollisionManager;
class GameMaster;
class HudNumber;
class ObjectBase;
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

  // Reset
  void Reset(void);

  // Push
  void Attach2D(ObjectBase* p_object);
  void Detatch2D(ObjectBase* p_object);

  // HACK:
  GameMaster& GetGameMaster(void) const { return *p_game_master_; }
  Player& GetPlayer(void) const { return *p_player_; }
  PinManager& GetPinManager(void) const { return *p_pin_manager_; }
  float GetSumTime(void) const { return sum_time_; }

  BulletManager& GetBulletManager(void) const { return *p_bullet_manager_; }

  void OnBulletUpdate(void) { is_bullet_update_ = true; }
  void OffBulletUpdate(void) { is_bullet_update_ = false; }

private:
  // Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;

  // Draw
  virtual void _Draw(void) override;

  GameState* p_game_state_;
  GameState* p_next_game_state_;
  CollisionManager* p_collision_manager_;
  GameMaster* p_game_master_;

  Root* p_2d_root_;
  Root* p_3d_root_;
  Player* p_player_;

  PinManager* p_pin_manager_;
  HudNumber** pp_hud_numbers_;
  float sum_time_;

  BulletManager* p_bullet_manager_;
  bool is_bullet_update_;
};
