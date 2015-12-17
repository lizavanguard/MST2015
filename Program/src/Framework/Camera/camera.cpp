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
    // HACK:
    auto p_device = DeviceHolder::Instance().GetDevice();
    D3DXMatrixLookAtLH(&view_, &eye_, &at_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    p_device->SetTransform(D3DTS_VIEW, &view_);

    D3DXMatrixPerspectiveFovLH(&projection_, kFov, kAspect, kNear, kFar);
    p_device->SetTransform(D3DTS_PROJECTION, &projection_);
  }

  if (p_camera_steering_) {
    p_camera_steering_->Execute(*this, elapsed_time);
  }
}

//------------------------------------------------
// assign
//------------------------------------------------
void Camera::AssignCameraSteering(CameraSteering* p_camera_steering) {
  SafeDelete(p_camera_steering_);
  p_camera_steering_ = p_camera_steering;
}
