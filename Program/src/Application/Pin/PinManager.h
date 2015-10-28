//==============================================================================
//
// PinManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class StandardPins;
class LanePins;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class PinManager : public ObjectBase {
public:
  // ctor
  PinManager();

  // dtor
  ~PinManager();

  // get
  const StandardPins& GetStandardPins(void) const { return *p_standard_pins_; }
  const LanePins& GetLanePins(void) const { return *p_lane_pins_; }

private:
  virtual void _Update(float elapsed_time) override {}
  virtual void _Draw(void) override {}

  StandardPins* p_standard_pins_;
  LanePins* p_lane_pins_;
};

using PinManagerFactory = liza::generic::Factory<PinManager>;
