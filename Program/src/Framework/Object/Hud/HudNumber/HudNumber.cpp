//==============================================================================
//
// HudNumber [HudNumber.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "HudNumber.h"
#include "../HudOverlay/HudOverlay.h"

#include "liza/utility/Counter/Counter.h"
#include "liza/utility/Utility/Utility.h"

#include "Framework/Texture/texture_manager.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
HudNumber::HudNumber(const unsigned int placeMax, const Vector2& pos, const Vector2& size, bool isFixed)
  : pTexture_(nullptr)
  , pCounter_(nullptr)
  , placeMax_(placeMax)
  , isFixed_(isFixed)
  , size_(size)
{
  // if ������0�Ȃ� �������Ȃ�
  if (placeMax_ == 0) {
    _ASSERT(placeMax_ != 0);
    return;
  }

  // �J�E���^�[����
  pCounter_ = new liza::utility::Counter(0, placeMax);

  // �T�C�Y�v�Z
  const float halfWidth = size.x / 2.0f;
  const float unitWidth = size.x / placeMax_;
  const float unitHalfWidth = unitWidth / 2.0f;
  const float startX = (pos.x - halfWidth);

  // �e������
  for (unsigned int placeCnt = 0; placeCnt < placeMax_; ++placeCnt) {
    this->AttachChild( new HudOverlay(
      Vector2(startX + (placeCnt * unitWidth) + unitHalfWidth, pos.y),
      0,
      Vector2(unitWidth, size.y)
      ));
  }

  // UV�l�Ȃǂ̍X�V
  _UpdateUV();

  if (isFixed_) {
    _FixPlace(0);
  }

  pTexture_ = TextureManager::Instance().Find("General/number_UI");
}


//------------------------------------------------
// dtor
//------------------------------------------------
HudNumber::~HudNumber() {
  SafeDelete(pCounter_);
}

//------------------------------------------------
// _Update
//------------------------------------------------
void HudNumber::_Update(const float elapsed_time) {
}
void HudNumber::UpdatePos(const D3DXVECTOR2& pos) {
  const float halfWidth = size_.x / 2.0f;
  const float unitWidth = size_.x / placeMax_;
  const float unitHalfWidth = unitWidth / 2.0f;
  const float startX = (pos.x - halfWidth);

  for (int i = 0; i < placeMax_; ++i) {
    auto& hud = this->GetChild(i);
    HudOverlay& overlay = static_cast<HudOverlay&>(hud);
    overlay.UpdatePos(Vector2(startX + (i * unitWidth) + unitHalfWidth, pos.y));
  }
}

//------------------------------------------------
// Draw
//------------------------------------------------
void HudNumber::_Draw(void) {
  // �`�悵�Ȃ����������߂�
  unsigned int invisiblePlaceMax = placeMax_ - pCounter_->GetPlaceMax();
  DeviceHolder::Instance().GetDevice()->SetTexture(0, pTexture_);

  for (unsigned int placeCnt = 0; placeCnt < invisiblePlaceMax; ++placeCnt) {
    auto& child = GetChild(placeCnt);
    child.OffAllDrawed();
  }
}


//------------------------------------------------
// Add Number
//------------------------------------------------
void HudNumber::AddNumber(const unsigned int number) {
  if (isFixed_) {
    _FixPlace(pCounter_->GetValue() + number);
  }
  pCounter_->AddValue(number);
  _UpdateUV();
}


//------------------------------------------------
// Assign number
//------------------------------------------------
void HudNumber::AssignNumber(const unsigned int number) {
  if (isFixed_) {
    _FixPlace(number);
  }
  pCounter_->SetValue(number);
  _UpdateUV();
}


//------------------------------------------------
// Dec number
//------------------------------------------------
void HudNumber::DecNumber(const unsigned int number) {
  if (isFixed_) {
    _FixPlace(pCounter_->GetValue() - number);
  }
  pCounter_->DecValue(number);
  _UpdateUV();
}



//------------------------------------------------
// Change sub place max
//------------------------------------------------
void HudNumber::ChangeSubPlaceMax(unsigned int subPlaceMax) {
  // if �T�u�̍ő包�����C���̍ő包���傫���ꍇ �ő包�ɍ��킹��
  if (subPlaceMax > placeMax_) {
    subPlaceMax = placeMax_;
  }

  // �T�u�̕\�����ɍ��킹��
  pCounter_->ChangePlaceMax(subPlaceMax);
  _UpdateUV();
}


//------------------------------------------------
// get
//------------------------------------------------
unsigned int HudNumber::GetSubPlaceMax(void) const {
  return pCounter_->GetPlaceMax();
}


//------------------------------------------------
// UV�l�Ȃǂ̍X�V
//------------------------------------------------
void HudNumber::_UpdateUV(void) {
  // ���l�ɉ�����uv�l���v�Z����
  const unsigned int number = pCounter_->GetValue();
  for (unsigned int placeCnt = 0; placeCnt < placeMax_; ++placeCnt) {
    // ���l�f�[�^�̕\���X�V
    // ���̒l�����o��
    const int value = (number / (int)(powf((float)10, (float)placeMax_ - placeCnt - 1))) % 10;
    auto& child = GetChild(placeCnt);
    static_cast<HudOverlay&>(child).ChangeUV(0.1f * value, 0.1f * value + 0.1f, 0.0f, 1.0f);
  }
}


//------------------------------------------------
// ���݂̒l�Ɍ������킹��
//------------------------------------------------
void HudNumber::_FixPlace(int value) {
  // ���݂̌��������߂�
  unsigned int placeCnt = liza::utility::CalcPlaceCnt(value < 0 ? 0 : value);

  // if �ő包�𒴂��Ă�����͈͓��Ɏ��߂�
  if (placeCnt > placeMax_) {
    placeCnt = placeMax_;
  }

  // ���݂̌����ɍ��킹��
  pCounter_->ChangePlaceMax(placeCnt);
}