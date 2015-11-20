//==============================================================================
//
// Object2D
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
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2DSteering;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2D : public ObjectBase {
public:
  // ctor
  Object2D(const char* p_filename, const D3DXVECTOR3& position, const D3DXVECTOR2& size, Object2DSteering* p_steering = nullptr);

  // dtor
  virtual ~Object2D();

  // set
  void SetUVCorner(float left, float top, float right, float bottom) {
    uv_left_top_.x = left; uv_left_top_.y = top;
    uv_right_bottom_.x = right; uv_right_bottom_.y = bottom;
  }
  void SetAlpha(float alpha) { alpha_ = alpha; }
  void SetSize(float width, float height) { size_.x = width; size_.y = height; }

  // Assign steering
  void AssignSteering(Object2DSteering* p_steering) {
    SafeDelete(p_steering_);
    p_steering_ = p_steering;
  }

private:
  // virtual function
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  // property
  LPD3DXEFFECT p_shader_;
  PDIRECT3DVERTEXDECLARATION9 p_declaration_;
  LPDIRECT3DTEXTURE9 p_texture_;
  D3DXVECTOR2 size_;
  float alpha_;
  D3DXVECTOR2 uv_left_top_;
  D3DXVECTOR2 uv_right_bottom_;
  Object2DSteering* p_steering_;
};

using Object2DFactory = liza::generic::Factory<Object2D>;