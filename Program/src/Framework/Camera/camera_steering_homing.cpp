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
CameraSteeringHoming::CameraSteeringHoming(ObjectBase& target,
                                           const float eye_distance,
                                           const float eye_height,
                                           const float at_distance)
    : target_(target)
    , eye_distance_(eye_distance)
    , eye_height_(eye_height)
    , at_distance_(at_distance)
    , rotation_(0.0f) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringHoming::~CameraSteeringHoming() {
}

//------------------------------------------------
// Execute
//------------------------------------------------
void CameraSteeringHoming::Execute(Camera& camera, const float elapsed_time) {
  const D3DXVECTOR3 target_position = target_.GetPosition();
  const float target_rotation = target_.GetRotation().y + rotation_;
  const D3DXVECTOR3 target_speed = target_.GetSpeed();

  const float sin = sinf(target_rotation);
  const float cos = cosf(target_rotation);

  const D3DXVECTOR3 target_true_position = target_position + target_speed * elapsed_time;
  D3DXVECTOR3 camera_eye = target_true_position;
  camera_eye.x -= sin * eye_distance_;
  camera_eye.z -=  cos * eye_distance_;
  camera_eye.y += eye_height_;
  SetEye(camera, camera_eye);

  D3DXVECTOR3 camera_at = target_true_position;
  camera_at.x += sin * at_distance_;
  camera_at.z += cos * at_distance_;
  SetAt(camera, camera_at);
}
