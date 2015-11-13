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
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneGame : public Scene {
public:
  // ctor
  SceneGame();

  // dtor
  virtual ~SceneGame();

private:
  // Update
  virtual void _Update(SceneManager* p_scene_manager, float elapsed_time) override;

  // Draw
  virtual void _Draw(void) override;
};
