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
#include "creator.h"
#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class DebugObject : public ObjectBase, public Creator<DebugObject> {
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
