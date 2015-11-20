//==============================================================================
//
// Object2DSteeringFlashing
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
class Object2DSteeringFlashing : public Object2DSteering {
public:
  // ctor
  Object2DSteeringFlashing()
      : time_(0.0f)
      , speed_rate_(1.0f) {
  }

  // dtor
  virtual ~Object2DSteeringFlashing() {}

  // Update
  virtual void Update(Object2D& object, float elapsed_time);

  // set
  void SetSpeedRate(float speed_rate) { speed_rate_ = speed_rate; }

private:
  float time_;
  float speed_rate_;
};
