//==============================================================================
//
// Pin
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "Framework/Object/object_model.h"
#include "Framework/Collision/collision_object.h"
#include "PinConfig.h"

#include "Framework/Bullet/BulletManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SceneGame;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Pin : public ObjectModel, public CollisionObject {
public:
  // ctor
  Pin(const D3DXVECTOR3& position, SceneGame* p_scene_game = nullptr, const char *p_filename = pin::kModelName);

  // dtor
  virtual ~Pin();

  // Reset
  virtual void Reset(void);

protected:
  // Update
  virtual void _Update(float elapsed_time) override;

private:
  D3DXVECTOR3 initial_position_;
  BulletManager::Handle handle_;
  SceneGame* p_scene_game_;
};

using PinFactory = liza::generic::Factory<Pin>;
