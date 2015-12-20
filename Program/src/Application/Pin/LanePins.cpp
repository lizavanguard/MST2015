//==============================================================================
//
// LanePins
// Author: Shimizu Shoji
//
// TODO:
//  INSTANCING-MODEL
//  ÉÇÉfÉãÇÃà íuìôÇê›íËÇ≈Ç´ÇÈÇÊÇ§Ç…Ç∑ÇÈ
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "LanePins.h"
#include "LanePin.h"
#include "PinConfig.h"

#include "Framework/Object/object_instancing_model.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
LanePins::LanePins() : p_instancing_model_(nullptr) {
  for (int pin_count = 0; pin_count < pin::lane_pin::kNums; ++pin_count) {
    const D3DXVECTOR3 position = {0.0f, pin::lane_pin::kY, -10000.0f + pin::lane_pin::kDistanceBetweenPins * pin_count};
    //const float theta = sinf(pin::lane_pin::kCurveValue * pin_count);
    const float theta = cosf((D3DX_PI / pin::lane_pin::kNums) * pin_count);
    auto p_pin = LanePinFactory::Create(position, theta);
    pins_.push_back(p_pin);
    AttachChild(p_pin);
  }

  is_child_auto_drawed_ = false;

  p_instancing_model_ = new ObjectInstancingModel(pin::kModelName , pins_.size());

  this->is_child_auto_updated_ = false;
}

//------------------------------------------------
// dtor
//------------------------------------------------
LanePins::~LanePins() {
  SafeDelete(p_instancing_model_);
}

//------------------------------------------------
// Reset
//------------------------------------------------
void LanePins::Reset(void) {
  std::for_each(pins_.begin(), pins_.end(), [](LanePin* pin) { pin->Reset(); });
}

//------------------------------------------------
// Update
//------------------------------------------------
void LanePins::_Update(const float elapsed_time) {
  this->_UpdateChildAll(elapsed_time);
  for (unsigned int i = 0; i < pins_.size(); ++i) {
    p_instancing_model_->UpdateInstanceData(i, pins_[i]->GetPosition(), pins_[i]->GetRotation());
  }
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void LanePins::_Draw(void) {
  p_instancing_model_->DrawAll();
}
