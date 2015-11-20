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

protected:
  D3DXVECTOR3 speed_;

private:
  // Update
  virtual void _Update(float elapsed_time) override;

  D3DXVECTOR3 initial_position_;
};

using PinFactory = liza::generic::Factory<Pin>;
