//==============================================================================
//
// CameraSteeringSet
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
class CameraSteeringSet : public Camera::CameraSteering {
public:
  // ctor
  CameraSteeringSet(Camera& camera, ObjectBase& target);

  // dtor
  ~CameraSteeringSet();

  // set
  void SetAtValue(const D3DXVECTOR3& at);
  void SetEyeValue(const D3DXVECTOR3& eye);

  virtual void Update(float elapsed_time) override;
};
