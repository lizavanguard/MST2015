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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class LanePin : public Pin {
public:
  // ctor
  LanePin(const D3DXVECTOR3& position);

  // dtor
  ~LanePin();

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;
};

using LanePinFactory = liza::generic::Factory<LanePin>;
