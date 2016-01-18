//==============================================================================
//
// Object2DSteeringUVUpdating
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2DSteering.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2DSteeringUVUpdating : public Object2DSteering {
public:
  // ctor
  Object2DSteeringUVUpdating(float speed_rate_u = 1.0f, float speed_rate_v = 1.0f)
      : time_(0.0f)
      , speed_rate_u_(speed_rate_u)
      , speed_rate_v_(speed_rate_v) {
  }

  // dtor
  virtual ~Object2DSteeringUVUpdating() {}

  // Update
  virtual void Update(Object2D& object, float elapsed_time);

  // set
  void SetSpeedRateU(float speed_rate_u) { speed_rate_u_ = speed_rate_u; }
  void SetSpeedRateV(float speed_rate_v) { speed_rate_v_ = speed_rate_v; }

private:
  float time_;
  float speed_rate_u_;
  float speed_rate_v_;
};
