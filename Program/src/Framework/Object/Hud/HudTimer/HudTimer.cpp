//==============================================================================
//
// HudTimer [HudTimer.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "HudTimer.h"

#include <liza/utility/Timer/BoundedTimer.h>

#include "../HudNumber/HudNumber.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
  const int kNumOverlay = 2;
  const int kDecimalPlaceMax = 2;	// 小数点桁数は2ケタで十分
  const float kOverlayMarginX = 200.f;
  const float kDecimalOffsetX = 1.0f;
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
HudTimer::HudTimer(
  const unsigned int placeMax,	// 整数桁
  const unsigned int decimalPlaceMax,	// 小数点桁
  const Vector2& pos,
  const Vector2& size,
  bool isCountUp
  )
  : pHudNumber_(nullptr)
  , pHudDecimalNumber_(nullptr)
  , pTimer_(nullptr)
  , decimalPlaceMax_(decimalPlaceMax)
  , placeMax_(placeMax)
  , isEventHappened_(false)
  , isDecimalNumberActive_(decimalPlaceMax > 0)
  , isNumberActive_(placeMax > 0)
{
  // if 小数点桁が最大桁数を超えていたら 最大桁にあわせる
  if (decimalPlaceMax_ > kDecimalPlaceMax) {
    decimalPlaceMax_ = kDecimalPlaceMax;
  }

  // 桁の合計値を求める
  int sumPlace = placeMax_ + decimalPlaceMax_;

  // 各桁のサイズを求める
  Vector2 unitSize = size / (float)sumPlace;

  // 整数桁生成
  if (isNumberActive_) {
    pHudNumber_ = new HudNumber(placeMax_, pos, unitSize * (float)(placeMax_));
  }

  // 小数桁生成
  // TODO:オフセットをサイズからの比率にするとか
  if (isDecimalNumberActive_) {
    Vector2 decimalPos = pos;
    decimalPos.x += unitSize.x * ((placeMax_ / 2.f) + kDecimalOffsetX);
    pHudDecimalNumber_ = new HudNumber(decimalPlaceMax_, decimalPos, unitSize * (float)(decimalPlaceMax_));
  }

  // タイマー生成
  pTimer_ = new liza::utility::BoundedTimer(0, isCountUp, 0, 99, false);
}


//------------------------------------------------
// dtor
//------------------------------------------------
HudTimer::~HudTimer() {
  SafeDelete(pTimer_);
  SafeDelete(pHudDecimalNumber_);
  SafeDelete(pHudNumber_);
}


//------------------------------------------------
// Update
//------------------------------------------------
void HudTimer::Update(const float elapsedTime) {
  pTimer_->Update(elapsedTime);
  isEventHappened_ = pTimer_->IsEventHappened();
  _UpdateNumbers();
}


//------------------------------------------------
// Draw
//------------------------------------------------
void HudTimer::Draw(void) {
  if (isNumberActive_) {
    pHudNumber_->Draw();
  }
  if (isDecimalNumberActive_) {
    pHudDecimalNumber_->Draw();
  }
}


//------------------------------------------------
// Assign Time
//------------------------------------------------
void HudTimer::AssignTime(const float time) {
  pTimer_->SetRawTime(time);
  _UpdateNumbers();
}


//------------------------------------------------
// get
//------------------------------------------------
float HudTimer::GetTime(void) const {
  return pTimer_->GetRawTime();
}


//------------------------------------------------
// Update Number
//------------------------------------------------
void HudTimer::_UpdateNumbers(void) {
  if (isNumberActive_) {
    pHudNumber_->AssignNumber(pTimer_->GetSecond());
  }
  if (isDecimalNumberActive_) {
    pHudDecimalNumber_->AssignNumber(pTimer_->GetFormattedMSecond());
  }
}