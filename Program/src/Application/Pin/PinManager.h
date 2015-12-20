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
class BiggestPin;
class GoalPins;
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
  GoalPins& GetGoalPins(void) { return *p_goal_pins_; }
  const GoalPins& GetGoalPins(void) const { return *p_goal_pins_; }
  const StandardPins& GetStandardPins(void) const { return *p_standard_pins_; }
  LanePins& GetLanePins(void) const { return *p_lane_pins_; }
  BiggestPin& GetBiggestPin(void) { return *p_biggest_pin_; }

  // Reset
  void Reset(void);

private:
  virtual void _Update(float elapsed_time) override {}
  virtual void _Draw(void) override {}

  BiggestPin* p_biggest_pin_;
  GoalPins* p_goal_pins_;
  StandardPins* p_standard_pins_;
  LanePins* p_lane_pins_;
};

using PinManagerFactory = liza::generic::Factory<PinManager>;
