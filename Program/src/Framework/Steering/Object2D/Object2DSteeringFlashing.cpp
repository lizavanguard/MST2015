//==============================================================================
//
// Object2DSteeringFlashing
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2DSteeringFlashing.h"

#include "Framework/Object/object2d.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Update
//------------------------------------------------
void Object2DSteeringFlashing::Update(Object2D& object, const float elapsed_time) {
  time_ += elapsed_time * speed_rate_;

  object.SetAlpha(sin(time_) * 0.5f + 0.5f);
}