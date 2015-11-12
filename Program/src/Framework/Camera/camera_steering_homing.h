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
  CameraSteeringHoming(ObjectBase& target);

  // dtor
  ~CameraSteeringHoming();

  // Execute
  virtual void Execute(Camera& camera, float elapsed_time) override;

private:
  ObjectBase& target_;
};
