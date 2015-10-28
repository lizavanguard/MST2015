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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Pin : public ObjectModel {
public:
  // ctor
  Pin(const D3DXVECTOR3& position);

  // dtor
  virtual ~Pin();

  // Reset
  void Reset(void);

  // Get
  float GetSize(void) const;

  // React collision
  void ReactCollision(void) { is_all_drawed_ = false; }
};

using PinFactory = liza::generic::Factory<Pin>;
