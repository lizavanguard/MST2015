//==============================================================================
//
// CameraSteeringHoming
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_steering_homing.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CameraSteeringHoming::CameraSteeringHoming(Camera& camera, ObjectBase& target)
    : CameraSteering(camera, target) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringHoming::~CameraSteeringHoming() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void CameraSteeringHoming::Update(const float) {
  const D3DXVECTOR3 target_position = GetTargetPosition();
  const D3DXVECTOR3 target_rotation = GetTargetRotation();
  const D3DXVECTOR3 target_velocity = GetTargetVelocity();

  const float sin = sinf(target_rotation.y);
  const float cos = cosf(target_rotation.y);

  D3DXVECTOR3 camera_eye = target_position + target_velocity;
  static const float kEyeDistance = 15.0f;
  static const float kEyeHeight = 10.0f;
  camera_eye.x -=  sin * kEyeDistance;
  camera_eye.z -=  cos * kEyeDistance;
  camera_eye.y += kEyeHeight;
  SetEye(camera_eye);

  D3DXVECTOR3 camera_at = camera_eye;
  static const float kAtDistance = 40.0f;
  camera_at.x += sin * kAtDistance;
  camera_at.z += cos * kAtDistance;
  SetAt(camera_at);
}
