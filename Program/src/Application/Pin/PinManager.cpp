//==============================================================================
//
// PinManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "PinManager.h"

#include "GoalPins.h"
#include "StandardPins.h"
#include "LanePins.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
PinManager::PinManager()
    : p_goal_pins_(nullptr)
    , p_standard_pins_(nullptr)
    , p_lane_pins_(nullptr) {
  const float kZ = 120.0f;
  const float kGoalPinR = 50.0f;
  AttachChild(p_goal_pins_ = GoalPinsFactory::Create(D3DXVECTOR3(-50, 10, 0), kGoalPinR));
  AttachChild(p_standard_pins_ = StandardPinsFactory::Create(D3DXVECTOR3(0, 0, kZ), D3DXVECTOR3(0, 0, 0)));
  AttachChild(p_lane_pins_ =  LanePinsFactory::Create());
}

//------------------------------------------------
// dtor
//------------------------------------------------
PinManager::~PinManager() {
}

//------------------------------------------------
// Reset
//------------------------------------------------
void PinManager::Reset(void) {
  p_goal_pins_->Reset();
  p_standard_pins_->Reset();
  p_lane_pins_->Reset();
}
