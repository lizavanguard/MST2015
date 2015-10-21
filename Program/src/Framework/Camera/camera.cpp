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

#include "window_config.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kFov = D3DX_PI / 2.0f;
  const float kAspect = kWindowWidth / (float)kWindowHeight;
  const float kNear = 1.0f;
  const float kFar = 1000.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Camera::Camera(const D3DXVECTOR3& eye, const D3DXVECTOR3& at)
    : eye_(eye)
    , at_(at) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Camera::~Camera() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Camera::Update(const float elapsed_time) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  D3DXMatrixLookAtLH(&view_, &eye_, &at_, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
  p_device->SetTransform(D3DTS_VIEW, &view_);

  D3DXMatrixPerspectiveFovLH(&projection_, kFov, kAspect, kNear, kFar);
  p_device->SetTransform(D3DTS_PROJECTION, &projection_);
}
