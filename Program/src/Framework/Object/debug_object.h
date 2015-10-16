//==============================================================================
//
// Debug Object
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
class DebugObject : public Object<DebugObject> {
public:
  // ctor
  DebugObject(const char* message)
#ifdef _DEBUG
    : message_(message)
#endif
  {
  }

  // dtor
  virtual ~DebugObject() {}

private:
  // Update
  virtual void _Update(float) final {
#ifdef _DEBUG
    DebugProc::Print("DebugObject::Update[%s]\n", message_.c_str());
#endif
  }

  // Draw
  virtual void _Draw(void) final {
#ifdef _DEBUG
    DebugProc::Print("DebugObject::Draw[%s]\n", message_.c_str());
#endif
  }

private:
#ifdef _DEBUG
  std::string message_;
#endif
};
