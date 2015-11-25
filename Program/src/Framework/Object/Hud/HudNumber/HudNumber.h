//==============================================================================
//
// HudNumber [HudNumber.h]
// Created : Shimizu Shoji
// MEMO:
//  �ő包�ƃT�u�ő包������
//  �Ⴆ�΃Q�[���̗��_��̍ő�l��5�P�^[99999]���Ƃ���
//  ���݂�HP�Ȃǂ�3�P�^[999]���Ƃ���
//  ���̎��͍ő包��5,�T�u�ő包��3������
//  �������̂܂܂̏ꍇ��00999�Ȃǂ̂悤�ɕ\�������
//  �܂��A�T�u�ő包�͍ő包�𒴂��邱�Ƃ��ł��Ȃ�
//
//==============================================================================
#pragma once
#ifndef __H_HUDNUMBER_H__
#define __H_HUDNUMBER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Object/object_base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HudOverlay;

namespace liza {
  namespace utility {
    class Counter;
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HudNumber : public ObjectBase {
public:
  // ctor
  // �ő包, ���S���W, �S�̃T�C�Y
  HudNumber(unsigned int placeMax, const Vector2& pos, const Vector2& size, bool isFixed = false);

  // dtor
  ~HudNumber();

  // Add number
  void AddNumber(unsigned int number);

  // Assign number
  void AssignNumber(unsigned int number);

  // Dec number
  void DecNumber(unsigned int number);

  // Change sub place max
  void ChangeSubPlaceMax(unsigned int subPlaceMax);

  // get
  unsigned int GetPlaceMax(void) const { return placeMax_; }
  unsigned int GetSubPlaceMax(void) const;

private:
  virtual void _Update(float elapsed_time) override {}
  virtual void _Draw(void) override;

  // UV�l�Ȃǂ̍X�V
  void _UpdateUV(void);

  // ���݂̒l�Ɍ������킹��
  void _FixPlace(int value);

  // property
  LPDIRECT3DTEXTURE9 pTexture_;
  liza::utility::Counter* pCounter_;
  unsigned int placeMax_;	// ���C���̍ő包
  bool isFixed_;
};


#endif // __H_HUDNUMBER_H__