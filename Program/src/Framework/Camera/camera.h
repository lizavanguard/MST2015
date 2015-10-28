//==============================================================================
//
// Camera
// Author: Shimizu Shoji
//
// Required:
//  1. homing target
//  2. free control(debug)
//  3. move to
//
// command maybe conflict
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

class CameraSteeringFixed;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Camera {
public:
  friend class CameraSteeringFixed;

public:
  // ctor
  Camera(const D3DXVECTOR3& eye, const D3DXVECTOR3& at);

  // dtor
  ~Camera();

  // get
  const D3DXMATRIX& GetProjectionMatrix(void) const { return projection_; }
  const D3DXMATRIX& GetViewMatrix(void) const { return view_; }

  virtual void Update(float elapsed_time);

  // assign
  void AssignCameraSteering(CameraSteeringFixed* p_camera_steering);

private:
  // property
  D3DXMATRIX projection_;
  D3DXMATRIX view_;

  D3DXVECTOR3 eye_;
  D3DXVECTOR3 at_;

  CameraSteeringFixed* p_camera_steering_;
};

using CameraFactory = liza::generic::Factory<Camera>;
