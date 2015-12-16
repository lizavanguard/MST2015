//==============================================================================
//
// PinConfig
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace pin {
  // general
  static const char* kModelName = "pin_05";

  // goal pin
  namespace goal_pin {
    static const D3DXVECTOR3 kPosition(0.0f, 10.0f, 10000.0f);
    static const float kR = 1500.0f;
    static const float kImpactPower = 5000000.0f;
    static const unsigned int kNumCircles = 4;
  }

  // lane pin
  namespace lane_pin {
    static const float kNums = 100;
    static const float kDistanceBetweenPins = 1000.0f;
    static const float kCurveValue = 0.1f;
    static const float kImpactPower = 5000.0f;
    static const float kImpactHeight = 2000.0f;
    static const float kImpactSide = 3000.0f;
    static const float kY = 100.0f;
    static const float kMovingDistance = 1000.0f;
    static const float kMovingSpeed = 1.0f;
  }

  // biggest pin
  namespace biggest_pin {
    static const float kScale = 5.0f;
    static const D3DXVECTOR3 kPosition(0.0f, 0.0f, 10000.0f);
    static const D3DXVECTOR3 kTitlePosition(0.0f, 0.0f, 100000.0f);
  }
}