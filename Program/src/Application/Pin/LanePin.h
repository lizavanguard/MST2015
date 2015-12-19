//==============================================================================
//
// LanePin
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Pin.h"
#include "Framework/Effect/EffectManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class LanePin : public Pin {
public:
  // ctor
  LanePin(const D3DXVECTOR3& position, float theta);

  // dtor
  ~LanePin();

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

  // Reset
  virtual void Reset(void) override;

private:
  // _function
  virtual void _Update(float elapsed_time) override;

  // property
  EffectManager::Handle3D handle_;
  D3DXVECTOR3 base_position_;
  float rotation_speed_;
  float theta_;
  float initial_theta_;
};

using LanePinFactory = liza::generic::Factory<LanePin>;
