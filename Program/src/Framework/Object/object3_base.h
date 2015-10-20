//==============================================================================
//
// Object3DBase
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3DBase : public Object<Object3DBase> {
public:
  // ctor
  Object3DBase()
      : position_(0.0f, 0.0f, 0.0f)
      , rotation_(0.0f, 0.0f, 0.0f)
      , scale_(1.0f, 1.0f, 1.0f)
      , velocity_(0.0f, 0.0f, 0.0f) {
  }

  // dtor
  virtual ~Object3DBase() {}

  void MoveForward(void) {
    position_ += velocity_;
  }

protected:
  // property
  D3DXVECTOR3 position_;
  D3DXVECTOR3 rotation_;
  D3DXVECTOR3 scale_;
  D3DXVECTOR3 velocity_;

private:
  // Update
  virtual void _Update(float elapsed_time) = 0;

  // Draw
  virtual void _Draw(void) = 0;
};
