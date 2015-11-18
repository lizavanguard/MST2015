//==============================================================================
//
// Pin
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "Framework/Object/object_model.h"
#include "Framework/Collision/collision_object.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Pin : public ObjectModel, public CollisionObject {
public:
  // ctor
  Pin(const D3DXVECTOR3& position);

  // dtor
  virtual ~Pin();

  // Reset
  void Reset(void);

private:
  D3DXVECTOR3 initial_position_;
};

using PinFactory = liza::generic::Factory<Pin>;
