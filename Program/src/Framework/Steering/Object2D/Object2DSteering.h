//==============================================================================
//
// Object2DSteering
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2D;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// INTERFACE
class Object2DSteering {
public:
  // ctor
  Object2DSteering() {}

  // dtor
  virtual ~Object2DSteering() {}

  // Update
  virtual void Update(Object2D& object, float elapsed_time) = 0;

};

// NULL OBJECT
class NullObject2DSteering : public Object2DSteering {
public:
  // ctor
  NullObject2DSteering() {}

  // Update
  virtual void Update(Object2D&, float) override {}
};
