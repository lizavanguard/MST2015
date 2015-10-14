//==============================================================================
//
// Root Object
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
class Root : public Object {
public:
  // ctor
  Root() {}

  // dtor
  virtual ~Root() {}

  // Initialize
  bool Initialize(void) {
    return true;
  }

  // Uninitialize
  bool Uninitialize(void) {
    return true;
  }

private:
  // Update
  virtual void _Update(float) final {
    DebugProc::Print("ROOT::Update\n");
  }

  // Draw
  virtual void _Draw(void) final {
    DebugProc::Print("ROOT::Draw\n");
  }
};
