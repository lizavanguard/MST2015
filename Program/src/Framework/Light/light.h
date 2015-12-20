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
  const D3DXVECTOR3 kDirection = D3DXVECTOR3(0.0f, -0.5f, 1.0f);
  const float kAmbient = 0.3f;

public:
  // ctor
  Light() : direction_(kDirection), ambient_(kAmbient) {
    D3DXVec3Normalize(&direction_, &direction_);
  }

  // dtor
  ~Light() {}

  // get
  const D3DXVECTOR3& GetDirection() const { return direction_; }
  float GetAmbient(void) const { return ambient_; }

private:
  D3DXVECTOR3 direction_;
  float ambient_;
};

#include "liza/generic/ServiceLocator.hpp"
using LightServiceLocator = liza::generic::ServiceLocator<Light>;
