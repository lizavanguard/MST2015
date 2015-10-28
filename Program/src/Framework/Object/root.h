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
#include "liza/generic/factory.hpp"

#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Root : public ObjectBase {
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

using RootFactory = liza::generic::Factory<Root>;
