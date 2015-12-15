//==============================================================================
//
// CameraSteeringHoming
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CameraSteeringHoming : public Camera::CameraSteering {
private:
  // const
  const float kRotationSpeed = 0.1f;

public:
  // ctor
  CameraSteeringHoming(ObjectBase& target, float eye_distance, float eye_height, float at_distance);

  // dtor
  ~CameraSteeringHoming();

  // Execute
  virtual void Execute(Camera& camera, float elapsed_time) override;

  // set
  void RotateLeft(void)  { rotation_ -= kRotationSpeed; }
  void RotateRight(void) { rotation_ += kRotationSpeed; }
  void SetRotationY(float rotation) { rotation_ = rotation; }

private:
  ObjectBase& target_;
  float eye_distance_;
  float eye_height_;
  float at_distance_;
  float rotation_;
};
