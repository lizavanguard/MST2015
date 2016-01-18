//==============================================================================
//
// StandardPin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "StandardPin.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
StandardPin::StandardPin(const D3DXVECTOR3& position, SceneGame* p_scene_game) : Pin(position, p_scene_game) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
StandardPin::~StandardPin() {
}

//------------------------------------------------
// React collision
//------------------------------------------------
void StandardPin::ReactCollision(const D3DXVECTOR3& power) {
  D3DXVECTOR3 direction;
  D3DXVec3Normalize(&direction, &power);
  const float impact_power = D3DXVec3Length(&power);

  speed_ += direction * impact_power * 10;
  is_all_drawed_ = true;
  is_collided_ = true;
};
