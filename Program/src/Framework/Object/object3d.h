//==============================================================================
//
// Object3D
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3D : public ObjectBase {
public:
  // ctor
  Object3D(const char* p_filename);

  // dtor
  virtual ~Object3D();

  // set
  void SetUVCorner(float left, float top, float right, float bottom) {
    uv_left_top_.x = left; uv_left_top_.y = top;
    uv_right_bottom_.x = right; uv_right_bottom_.y = bottom;
  }
  void OnBottomCentered(void) { is_bottom_centered_ = true; }
  void OffBottomCentered(void) { is_bottom_centered_ = false; }

private:
  // virtual function
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  // property
  LPD3DXEFFECT p_shader_;
  PDIRECT3DVERTEXDECLARATION9 p_declaration_;
  LPDIRECT3DTEXTURE9 p_texture_;
  D3DXVECTOR2 uv_left_top_;
  D3DXVECTOR2 uv_right_bottom_;
  bool is_bottom_centered_;  // 中心が重心位置かどうか
};

using Object3DFactory = liza::generic::Factory<Object3D>;