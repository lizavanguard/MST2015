//==============================================================================
//
// HudNumber [HudNumber.h]
// Created : Shimizu Shoji
// MEMO:
//  最大桁とサブ最大桁が存在
//  例えばゲームの理論上の最大値が5ケタ[99999]だとして
//  現在のHPなどが3ケタ[999]だとする
//  その時は最大桁に5,サブ最大桁に3を入れる
//  もしそのままの場合は00999などのように表示される
//  また、サブ最大桁は最大桁を超えることができない
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
  // 最大桁, 中心座標, 全体サイズ
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

  // UV値などの更新
  void _UpdateUV(void);

  // 現在の値に桁を合わせる
  void _FixPlace(int value);

  // property
  LPDIRECT3DTEXTURE9 pTexture_;
  liza::utility::Counter* pCounter_;
  unsigned int placeMax_;	// メインの最大桁
  bool isFixed_;
};


#endif // __H_HUDNUMBER_H__