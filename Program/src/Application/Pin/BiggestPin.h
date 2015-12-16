//==============================================================================
//
// BiggestPin
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
class BiggestPin : public Pin {
public:
  // ctor
  BiggestPin(const D3DXVECTOR3& position);

  // dtor
  ~BiggestPin();

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

  // Reset
  virtual void Reset(void) override;

private:
  // _function
  virtual void _Update(float elapsed_time) override;

  // property
  EffectManager::Handle3D handle_;
  D3DXVECTOR3 rotation_speed_;
};
