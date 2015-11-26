//==============================================================================
//
// GoalPins
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GoalPins.h"

#include "GoalPin.h"

template<int N>
struct CalculateCircleValue {
  enum { value = N + CalculateCircleValue<N - 1>::value };
};

template<>
struct CalculateCircleValue<0> {
  enum { value = 0};
};

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GoalPins::GoalPins(const D3DXVECTOR3& center_position, const float r) : CollisionObject(r) {
  position_ = center_position;
  // 円の段数
  //   : 1 => 中心のピン1本に全て重なる
  //   : 2 => 中心にピン1本 + その周りに残りのピン全て
  const unsigned int kNumCircles = 4 + 1;
  const unsigned int kSum = CalculateCircleValue<kNumCircles - 1>::value;
  const unsigned int kUnitNumPins = (kNumPins - 1) / kSum;
  const unsigned int kRestNumPins = (kNumPins - 1) - (kUnitNumPins * kSum);
  const float kDistance = r / kNumCircles;

  unsigned int index = 0;
  AttachChild(pins_[index++] = GoalPinFactory::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f)));

  for (unsigned int circle_count = 1; circle_count < kNumCircles; ++circle_count) {

    unsigned int num_pins = kUnitNumPins * circle_count;
    if (circle_count == kNumCircles - 1) {
      num_pins += kRestNumPins;
    }
    const float distance = kDistance * circle_count;
    const float kUnitTheta = (D3DX_PI * 2.0f) / num_pins;
    for (unsigned int pin_count = 0; pin_count < num_pins; ++pin_count) {
      const float theta = kUnitTheta * pin_count;
      const D3DXVECTOR3 position(cosf(theta) * distance, 0.0f, sinf(theta) * distance);
      AttachChild(pins_[index++] = GoalPinFactory::Create(position));
    }
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
GoalPins::~GoalPins() {
}

//------------------------------------------------
// Reset
//------------------------------------------------
void GoalPins::Reset(void) {
  std::for_each(pins_.begin(), pins_.end(), [](GoalPin* pin) { pin->Reset(); });
  is_collided_ = false;
}

//------------------------------------------------
// React collision
// power = collision position
//------------------------------------------------
void GoalPins::ReactCollision(const D3DXVECTOR3& power) {
  D3DXVECTOR3 relative_position = power - position_;
  std::for_each(pins_.begin(), pins_.end(), [&relative_position](GoalPin* pin) { pin->ReactCollision(relative_position); });
  is_collided_ = true;
}