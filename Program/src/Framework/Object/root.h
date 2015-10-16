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
class Root : public Object<Root> {
public:
  // ctor
  Root() {}

  // dtor
  virtual ~Root() {}

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
