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
    , p_camera_steering_(new NullCameraSteeringObject()) {
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
// _Update view matrix
//------------------------------------------------
void Camera::_UpdateViewMatrix(void) {
  D3DXMatrixLookAtLH(&view_, &eye_, &at_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

void Camera::_UpdateProjectionMatrix(void) {
  D3DXMatrixPerspectiveFovLH(&projection_, kFov, kAspect, kNear, kFar);
}
