//==============================================================================
//
// Object2DSteeringMoving
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2DSteeringMoving.h"

#include "liza/math/Interpolation.hpp"

#include "Framework/Object/object2d.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Update
//------------------------------------------------
void Object2DSteeringMoving::Update(Object2D& object, const float elapsed_time) {
  const float t = std::min<float>((sum_time_ / time_), 1.0f);

  object.SetPosition(liza::math::InterpolateQuadraticEaseOut(t, position_a_, position_b_));

  sum_time_ += elapsed_time;
}
