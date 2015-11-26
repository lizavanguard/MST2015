//==============================================================================
//
// GoalPin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GoalPin.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GoalPin::GoalPin(const D3DXVECTOR3& position) : Pin(position) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
GoalPin::~GoalPin() {
}

//------------------------------------------------
// React collision
// power = collision position
//------------------------------------------------
void GoalPin::ReactCollision(const D3DXVECTOR3& power) {
  D3DXVECTOR3 to_me = position_ - power;
  to_me.y = 0.0f;
  const float distance = D3DXVec3Length(&to_me);
  D3DXVECTOR3 direction;
  D3DXVec3Normalize(&direction, &to_me);

  float impact = 1000.0f / distance;
  speed_ = direction * impact;

  is_all_drawed_ = true;
  is_collided_ = true;
};
