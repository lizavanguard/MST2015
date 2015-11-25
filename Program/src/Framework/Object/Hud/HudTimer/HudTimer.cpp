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
  const int kDecimalPlaceMax = 2;	// �����_������2�P�^�ŏ\��
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
  const unsigned int placeMax,	// ������
  const unsigned int decimalPlaceMax,	// �����_��
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
  // if �����_�����ő包���𒴂��Ă����� �ő包�ɂ��킹��
  if (decimalPlaceMax_ > kDecimalPlaceMax) {
    decimalPlaceMax_ = kDecimalPlaceMax;
  }

  // ���̍��v�l�����߂�
  int sumPlace = placeMax_ + decimalPlaceMax_;

  // �e���̃T�C�Y�����߂�
  Vector2 unitSize = size / (float)sumPlace;

  // ����������
  if (isNumberActive_) {
    pHudNumber_ = new HudNumber(placeMax_, pos, unitSize * (float)(placeMax_));
  }

  // ����������
  // TODO:�I�t�Z�b�g���T�C�Y����̔䗦�ɂ���Ƃ�
  if (isDecimalNumberActive_) {
    Vector2 decimalPos = pos;
    decimalPos.x += unitSize.x * ((placeMax_ / 2.f) + kDecimalOffsetX);
    pHudDecimalNumber_ = new HudNumber(decimalPlaceMax_, decimalPos, unitSize * (float)(decimalPlaceMax_));
  }

  // �^�C�}�[����
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