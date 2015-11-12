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
  CameraSteeringFixed(ObjectBase& target);

  // dtor
  virtual ~CameraSteeringFixed();

  // Execute
  virtual void Execute(Camera& camera, float elapsed_time) override;

private:
  ObjectBase& target_;
};
