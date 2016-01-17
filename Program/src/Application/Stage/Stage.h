//==============================================================================
//
// Stage
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Bullet/BulletManager.h"
#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneGame;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Stage : public ObjectBase {
public:
  // ctor
  Stage(SceneGame* p_scene_game = nullptr);

  // dtor
  ~Stage();

private:
  // func
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  SceneGame* p_scene_game_;
  BulletManager::Handle handle_;
};
