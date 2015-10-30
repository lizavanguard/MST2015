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
public:
  // ctor
  CameraSteeringHoming(Camera& camera, ObjectBase& target);

  // dtor
  ~CameraSteeringHoming();

  virtual void Update(float elapsed_time) override;
};
