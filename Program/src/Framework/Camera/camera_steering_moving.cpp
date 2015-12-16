//==============================================================================
//
// CameraSteeringMoving
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_steering_moving.h"
#include "camera_steering_homing.h"
#include "camera.h"

#include "liza/math/Interpolation.hpp"

#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kEyeDistance = 100.0f;
  const float kEyeHeight = 10.0f;
  const float kAtDistance = 100.0f;
}

//==============================================================================
// class implementation
//==============================================================================
namespace {

class ControlableObject : public ObjectBase {
public:
  ControlableObject(const D3DXVECTOR3& position_a, const D3DXVECTOR3& position_b,
                    const float time)
     : position_a_(position_a)
     , position_b_(position_b)
     , time_(time)
     , sum_time_(0.0f) {
  }
  virtual ~ControlableObject() {}

private:
  virtual void _Update(float elapsed_time) override {
    float t = sum_time_ / time_;
    if (t > 1.0f) {
      t = 1.0f;
    }
    position_ = liza::math::InterpolateTrigonometric(t, position_a_, position_b_);

    sum_time_ += elapsed_time;
  }

  virtual void _Draw(void) override {}

  D3DXVECTOR3 position_a_;
  D3DXVECTOR3 position_b_;
  float time_;
  float sum_time_;
};

}

//------------------------------------------------
// ctor
//------------------------------------------------
CameraSteeringMoving::CameraSteeringMoving(const D3DXVECTOR3& position_a, const D3DXVECTOR3& position_b, const float time)
    : p_steering_(nullptr)
    , p_dummy_(nullptr) {
  p_dummy_ = new ControlableObject(position_a, position_b, time);
  p_steering_ = new CameraSteeringHoming(*p_dummy_, 600.0f, 200.0f, 0.1f);
}

// ダミーの座標がそのままカメラの中心座標になる
// 視点位置を固定にして注視点をダミーの座標にする
//
//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringMoving::~CameraSteeringMoving() {
  SafeDelete(p_steering_);
  ObjectBase::Destroy(p_dummy_);
}

//------------------------------------------------
// Execute
//------------------------------------------------
void CameraSteeringMoving::Execute(Camera& camera, const float elapsed_time) {
  p_dummy_->UpdateAll(elapsed_time);
  p_steering_->Execute(camera, elapsed_time);
}
