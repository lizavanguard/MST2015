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
  static const char* kBigModelName = "pin_scale18";

  // goal pin
  namespace goal_pin {
    static const D3DXVECTOR3 kPosition(0.0f, 10.0f, 10000.0f);
    static const float kR = 1500.0f;
    static const float kImpactPower = 5000000.0f;
    static const unsigned int kNumCircles = 4;
  }

  // lane pin
  namespace lane_pin {
    static const float kNums = 75;
    static const float kDistanceBetweenPins = 500.0f;
    static const float kCurveValue = 0.5;// 1f;
    static const float kImpactPower = 1000.0f;
    static const float kImpactHeight = 2000.0f;
    static const float kImpactSide = 500.0f;
    static const float kHalfSizeY = 267.802216f;
    static const float kY = kHalfSizeY;
    static const float kMovingDistance = 1000.0f;
    static const float kMovingSpeed = 0.3f;
  }

  // biggest pin
  namespace biggest_pin {
    static const float kScale = 5.0f;
    static const D3DXVECTOR3 kPosition(0.0f, 0.0f, 40000.0f);
    static const D3DXVECTOR3 kTitlePosition(0.0f, 0.0f, 40000.0f);
  }

  namespace standard_pin {
    static const D3DXVECTOR3 kPosition(0.0f, 0.0f, 20000.0f);
    static const D3DXVECTOR3 kTitlePosition(0.0f, lane_pin::kHalfSizeY, 38000.0f);
    static const float kDistance = 260.0f;
  }
}