//==============================================================================
//
// Object2DSteeringMoving
// Author: Shimizu Shoji
//
// 2Dオブジェクトの移動を制御する
// 座標Aから座標Bまでを補間して指定時間で移動させる
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object2DSteering.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object2DSteeringMoving : public Object2DSteering {
public:
  // ctor
  Object2DSteeringMoving(const D3DXVECTOR3& position_a, const D3DXVECTOR3& position_b, float time)
      : position_a_(position_a)
      , position_b_(position_b)
      , time_(time)
      , sum_time_(0.0f) {
  }

  // dtor
  virtual ~Object2DSteeringMoving() {}

  // Update
  virtual void Update(Object2D& object, float elapsed_time);

private:
  const D3DXVECTOR3 position_a_;
  const D3DXVECTOR3 position_b_;
  const float time_;
  float sum_time_;
};
