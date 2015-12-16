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

#include "BiggestPin.h"
#include "GoalPins.h"
#include "PinConfig.h"
#include "StandardPins.h"
#include "LanePins.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
PinManager::PinManager()
    : p_biggest_pin_(nullptr)
    , p_goal_pins_(nullptr)
    , p_standard_pins_(nullptr)
    , p_lane_pins_(nullptr) {
  AttachChild(p_biggest_pin_ = new BiggestPin(pin::biggest_pin::kPosition));
  //AttachChild(p_goal_pins_ = GoalPinsFactory::Create(pin::goal_pin::kPosition, pin::goal_pin::kR));
  //AttachChild(p_standard_pins_ = StandardPinsFactory::Create(D3DXVECTOR3(0, 0, kZ), D3DXVECTOR3(0, 0, 0)));
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
  p_biggest_pin_->Reset();
  //p_goal_pins_->Reset();
  //p_standard_pins_->Reset();
  p_lane_pins_->Reset();
}
