//==============================================================================
//
// Object2DSteeringUVUpdating
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2DSteeringUVUpdating.h"

#include "Framework/Object/object2d.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Update
//------------------------------------------------
void Object2DSteeringUVUpdating::Update(Object2D& object, const float elapsed_time) {
  time_ += elapsed_time;

  const float time_u = time_ * speed_rate_u_;
  const float su = time_u;//liza::math::CirculateClamp(time_u       , 0.0f, 3.0f);
  const float eu = time_u + 3.0f;//liza::math::CirculateClamp(time_u + 3.0f, 0.0f, 3.0f);

  const float time_v = time_ * speed_rate_v_;
  const float sv = time_v;//liza::math::CirculateClamp(time_v       , 0.0f, 1.0f);
  const float ev = time_v + 4.0f;//liza::math::CirculateClamp(time_v + 5.0f, 0.0f, 5.0f);

  object.SetUVCorner(su, sv, eu, ev);
}
