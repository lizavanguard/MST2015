//==============================================================================
//
// Player
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "Framework/Collision/collision_object.h"
#include "Framework/CubeTextureForEnvironmentMapping/CubeTextureForEnvironmentMapping.h"
#include "Framework/Effect/EffectManager.h"
#include "Framework/Object/object_base.h"


//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class PlayerBall;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Player : public ObjectBase, public CollisionObject {
public:
  // ctor
  Player(CubeTextureForEnvironmentMapping::ObjectDrawer* p_object_drawer);

  // dtor
  virtual ~Player();

  // Move
  void MoveForward(void);
  void MoveForward(float speed);
  void MoveBackward(void);
  void MoveLeft(void);
  void MoveRight(void);
  void MoveUp(void);
  void MoveDown(void);
  void MoveStop(void);

  // Shoot
  void Shoot(float rotation);

  // Reset
  void Reset(void);

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

  // Change
  void ChangeDrawingOuterFace(bool is_drawn_outer_face);

  // Draw
  // BeginSceneÇ∆EndSceneÇÃä‘Ç≈åƒÇ—èoÇµÇƒ
  void UpdateCubeMapping(void);


private:
  virtual void _Draw(void) override {}
  virtual void _Update(float elapsed_time) override;

  bool is_shot_;

  float adjusted_value_;
  float curve_reaction_;
  float moving_speed_;
  float shot_speed_;
  float control_speed_;

  PlayerBall* p_ball_;
  EffectManager::Handle3D h_wind_effect_;
  EffectManager::Handle3D h_fire_effect_;
};

using PlayerFactory = liza::generic::Factory<Player>;
