//==============================================================================
//
// CameraSteeringFixed
// Author: Shimizu Shoji
//
// 現在のカメラ位置からターゲットの位置を追従する？
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
class CameraSteeringFixed : public Camera::CameraSteering {
public:
  // ctor
  CameraSteeringFixed(Camera& camera, ObjectBase& target);

  // dtor
  virtual ~CameraSteeringFixed();

  // Update
  virtual void Update(float elapsed_time) override;
};
