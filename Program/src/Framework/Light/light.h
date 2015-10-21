//==============================================================================
//
// Light
// Author: Shimizu Shoji
//
// virtualize only update
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Light : public ObjectBase {
public:
  // ctor
  Light(int, int){}

  // dtor
  virtual ~Light(){}

private:
  // TODO:
  //virtual void _Update(float) {}
  virtual void _Update(float elapsed_time) {}

  // _Draw
  virtual void _Draw(void) final {}

  // property
};
