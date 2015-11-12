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
CameraSteeringHoming::CameraSteeringHoming(ObjectBase& target)
    : target_(target) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringHoming::~CameraSteeringHoming() {
}

//------------------------------------------------
// Execute
//------------------------------------------------
void CameraSteeringHoming::Execute(Camera& camera, const float) {
  const D3DXVECTOR3 target_position = target_.GetPosition();
  const D3DXVECTOR3 target_rotation = target_.GetRotation();
  const D3DXVECTOR3 target_velocity = target_.GetVelocity();

  const float sin = sinf(target_rotation.y);
  const float cos = cosf(target_rotation.y);

  D3DXVECTOR3 camera_eye = target_position + target_velocity;
  static const float kEyeDistance = 15.0f;
  static const float kEyeHeight = 10.0f;
  camera_eye.x -=  sin * kEyeDistance;
  camera_eye.z -=  cos * kEyeDistance;
  camera_eye.y += kEyeHeight;
  SetEye(camera, camera_eye);

  D3DXVECTOR3 camera_at = camera_eye;
  static const float kAtDistance = 40.0f;
  camera_at.x += sin * kAtDistance;
  camera_at.z += cos * kAtDistance;
  SetAt(camera, camera_at);
}
