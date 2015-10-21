//==============================================================================
//
// Object3D
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object3d_base.h"
#include "creator.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3D : public Object3DBase, public Creator<Object3D> {
public:
  // ctor
  Object3D(int);

  // dtor
  ~Object3D();

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;
};
