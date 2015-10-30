//==============================================================================
//
// StandardPin
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
class StandardPin : public Pin {
public:
  // ctor
  StandardPin(const D3DXVECTOR3& position);

  // dtor
  ~StandardPin();

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

private:
};

using StandardPinFactory = liza::generic::Factory<StandardPin>;
