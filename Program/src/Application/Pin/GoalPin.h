//==============================================================================
//
// GoalPin
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Pin.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GoalPin : public Pin {
public:
  // ctor
  GoalPin(const D3DXVECTOR3& position);

  // dtor
  ~GoalPin();

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;
};

using GoalPinFactory = liza::generic::Factory<GoalPin>;
