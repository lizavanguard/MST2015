//==============================================================================
//
// Object3DBase
// Author: Shimizu Shoji
//
// _Update/_Draw オーバーライドな
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "creator.h"
#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3DBase : public ObjectBase {
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
