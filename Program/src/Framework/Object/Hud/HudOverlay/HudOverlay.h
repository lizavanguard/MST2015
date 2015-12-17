//==============================================================================
//
// HUDÉÇÉWÉÖÅ[Éã [HudOverlay.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_HUDOVERLAY_H__
#define __H_HUDOVERLAY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Object/object_base.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HudOverlay : public ObjectBase {
public:
  // ctor/dtor
  HudOverlay(const Vector2& pos, float rot, const Vector2& size);
  virtual ~HudOverlay();

  // Update
  void UpdatePos(const Vector2& pos) { pos_ = pos; _UpdateAll(); }
  void UpdateRot(float rot) { rot_ = rot; _UpdateAll(); }
  void UpdateSize(const Vector2& size) { size_ = size; _UpdateAll(); }

  void AddPos(const Vector2& pos) { pos_ += pos; _UpdateAll(); }

  // Change
  void ChangeAlpha(float a);
  void ChangeColor(const D3DXVECTOR4& color);
  void ChangeColor(float r, float g, float b, float a);
  void ChangeUV(float su, float eu, float sv, float ev);

  // get
  const Vector2& GetPos(void) const { return pos_; }
  float GetRot(void) const { return rot_; }
  const Vector2& GetSize(void) const { return size_; }


private:
  // Draw
  virtual void _Update(float elapsed_time) override {}
  virtual void _Draw(void) override;

  // method
  void _UpdateAll(void);
  void _UpdateAngle(void);
  void _UpdateDiagonalLength(void);
  void _UpdatePos(void);

  // field
  LPDIRECT3DVERTEXBUFFER9 pVertexBuffer_;
  Vector2 pos_;
  float rot_;
  Vector2 size_;
  float length_;
  float angle_;
};


#endif // __H_HUDOVERLAY_H__