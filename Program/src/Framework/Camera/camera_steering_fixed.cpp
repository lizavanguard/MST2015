//==============================================================================
//
// CameraSteeringFixed
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_steering_fixed.h"
#include "camera.h"

#include "Framework/Object/object_base.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CameraSteeringFixed::CameraSteeringFixed(Camera& camera, ObjectBase& target)
    : CameraSteering(camera, target) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CameraSteeringFixed::~CameraSteeringFixed() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void CameraSteeringFixed::Update(const float elapsed_time) {
  const D3DXVECTOR3 target_position = target_.GetPosition();
  SetAt(target_.GetPosition());
}
