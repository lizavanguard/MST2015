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

#include "Framework/Object/object_base.h"
#include "Framework/Collision/collision_object.h"

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
  Player();

  // dtor
  virtual ~Player();

  // Move
  void MoveLeft(void);
  void MoveRight(void);

  // Shoot
  void Shoot(float rotation);

  // Reset
  void Reset(void);

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

  // get
  const D3DXVECTOR3& GetPosition(void) const { return position_; }

private:
  virtual void _Draw(void) override {}
  virtual void _Update(float elapsed_time) override;

  D3DXVECTOR3 speed_;
  bool is_shot_;

  float adjusted_value_;
  float curve_reaction_;
  float moving_speed_;
  float shot_speed_;

  PlayerBall* p_ball_;
};

using PlayerFactory = liza::generic::Factory<Player>;
