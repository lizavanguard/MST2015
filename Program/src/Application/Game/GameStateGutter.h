//==============================================================================
//
// GameStateGutter
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
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameStateGutter : public SceneGame::GameState {
public:
  // ctor
  GameStateGutter(SceneGame& scene_game);

  // dtor
  virtual ~GameStateGutter();

  // Update
  virtual void Update(float elapsed_time) override;

  // Draw
  virtual void Draw(void) override;

private:
  // _cotrol
  void _Control(void);

  // property
  Root* p_root_;
  float ready_time_;
  bool is_fading_out_;
  EffectManager::Handle2D h_gutter_;
};
