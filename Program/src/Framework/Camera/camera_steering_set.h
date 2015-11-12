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
  CameraSteeringSet();

  // dtor
  ~CameraSteeringSet();

  // Execute
  virtual void Execute(Camera& camera, float elapsed_time) override;

  // set
  void SetAtValue(const D3DXVECTOR3& at) { at_ = at; }
  void SetEyeValue(const D3DXVECTOR3& eye) { eye_ = eye; }

private:
  D3DXVECTOR3 at_;
  D3DXVECTOR3 eye_;
};
