//==============================================================================
//
// Camera
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Camera.h"
#include "Framework/Utility/DeviceHolder.h"

#include "camera_config.h"
#include "camera_steering_fixed.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Camera::Camera(const D3DXVECTOR3& eye, const D3DXVECTOR3& at)
    : eye_(eye)
    , at_(at)
    , p_camera_steering_(new NullCameraSteeringObject())
    , shaking_power_(0.0f)
    , shaking_end_time_(0.0f)
    , shaking_sum_time_(0.0f)
    , shaking_speed_(0.0f)
    , shaking_amount_(0.0f) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Camera::~Camera() {
  if (p_camera_steering_) {
    delete p_camera_steering_;
    p_camera_steering_ = nullptr;
  }
}

//------------------------------------------------
// Update
//------------------------------------------------
void Camera::Update(const float elapsed_time) {
  if (is_auto_update_) {
    _UpdateViewMatrix();
    _UpdateProjectionMatrix();
    _UpdateShaking(elapsed_time);

    auto p_device = DeviceHolder::Instance().GetDevice();
    p_device->SetTransform(D3DTS_VIEW, &view_);
    p_device->SetTransform(D3DTS_PROJECTION, &projection_);
  }

  p_camera_steering_->Execute(*this, elapsed_time);
}

//------------------------------------------------
// assign
//------------------------------------------------
void Camera::AssignCameraSteering(CameraSteering* p_camera_steering) {
  SafeDelete(p_camera_steering_);
  if (p_camera_steering) {
    p_camera_steering_ = p_camera_steering;
  }
  else {
    p_camera_steering_ = new NullCameraSteeringObject();
  }
  p_camera_steering_->Execute(*this, 0.0f);
  _UpdateViewMatrix();
}

//------------------------------------------------
// Start shaking
// time = —h‚ê‚éŽžŠÔ
// speed = —h‚ê‚é‘¬“x(—h‚ê‚ÌU•‘¬“x)
// power = —h‚ê•û‚Ì‘å‚«‚³(—h‚ê‚é‹——£)
//------------------------------------------------
void Camera::StartShaking(const float time, const float speed, const float power) {
  shaking_end_time_ = time;
  shaking_sum_time_ = 0.0f;
  shaking_speed_ = speed;
  shaking_power_ = power;
  shaking_amount_ = 0;
}

//------------------------------------------------
// Stop shaking
//------------------------------------------------
void Camera::StopShaking(void) {
  shaking_amount_ = 0.0f;
  shaking_sum_time_ = 0.0f;
  shaking_end_time_ = 0.0f;
  shaking_speed_ = 0.0f;
  shaking_power_ = 0.0f;
}

//------------------------------------------------
// _Update matrix
//------------------------------------------------
void Camera::_UpdateViewMatrix(void) {
  const D3DXVECTOR3 eye(eye_.x, eye_.y + shaking_amount_, eye_.z);
  const D3DXVECTOR3 at(at_.x, at_.y + shaking_amount_, at_.z);
  D3DXMatrixLookAtLH(&view_, &eye, &at, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

void Camera::_UpdateProjectionMatrix(void) {
  D3DXMatrixPerspectiveFovLH(&projection_, kFov, kAspect, kNear, kFar);
}

//------------------------------------------------
// _Update Shaking
//------------------------------------------------
void Camera::_UpdateShaking(const float elapsed_time) {
  if (shaking_end_time_ == 0) {
    return;
  }
  shaking_amount_ = sinf(shaking_sum_time_ * shaking_speed_) * shaking_power_;

  shaking_sum_time_ += elapsed_time;
  if (shaking_sum_time_ >= shaking_end_time_) {
    StopShaking();
  }
}
