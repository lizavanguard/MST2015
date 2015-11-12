//==============================================================================
//
// CameraSteeringSet
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_steering_set.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CameraSteeringSet::CameraSteeringSet() {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringSet::~CameraSteeringSet() {
}

//------------------------------------------------
// Execute
//------------------------------------------------
void CameraSteeringSet::Execute(Camera& camera, const float) {
  CameraSteering::SetAt(camera, at_);
  CameraSteering::SetEye(camera, eye_);
}
