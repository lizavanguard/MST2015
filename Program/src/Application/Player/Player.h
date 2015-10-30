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

#include "Framework/Object/object_model.h"

#include "Framework/Collision/collision_object.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Player : public ObjectModel, public CollisionObject {
public:
  // ctor
  Player();

  // dtor
  virtual ~Player();

  // Shoot
  void Shoot(const D3DXVECTOR3& direction);

  // Reset
  void Reset(void);

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

  // get
  const D3DXVECTOR3& GetPosition(void) const { return position_; }

private:
  virtual void _Update(float elapsed_time) override;
};

using PlayerFactory = liza::generic::Factory<Player>;
