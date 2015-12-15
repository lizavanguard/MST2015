//==============================================================================
//
// Light
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Light {
  const D3DXVECTOR3 kDirection = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

public:
  // ctor
  Light() : direction_(kDirection) {
    D3DXVec3Normalize(&direction_, &direction_);
  }

  // dtor
  ~Light() {}

  // get
  const D3DXVECTOR3& GetDirection() const { return direction_; }

private:
  D3DXVECTOR3 direction_;
};

#include "liza/generic/ServiceLocator.hpp"
using LightServiceLocator = liza::generic::ServiceLocator<Light>;
