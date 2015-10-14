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
class DebugObject : public Object {
public:
  // ctor
  DebugObject()
#ifdef _DEBUG
    : message_("")
#endif
  {
  }

  // dtor
  virtual ~DebugObject() {}

  // Initialize
  bool Initialize(const std::string& message) {
    message_ = message;
    return true;
  }

  // Uninitialize
  virtual bool _Uninitialize(void) final {
    return true;
  }


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
