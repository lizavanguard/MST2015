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

#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Camera {
public:
  // ÉJÉÅÉâÇÃìÆÇ´ÇÃíäè€ÉNÉâÉX
  class CameraSteering {
  public:
    // ctor
    CameraSteering(Camera& camera, ObjectBase& target)
        : camera_(camera), target_(target) {
    }

    // dtor
    virtual ~CameraSteering() {}

    // Update
    virtual void Update(float elapsed_time) = 0;

  protected:
    // get
    const D3DXVECTOR3& GetAt(void) const { return camera_.at_; }
    const D3DXVECTOR3& GetEye(void) const { return camera_.eye_; }
    const D3DXVECTOR3& GetTargetPosition(void) const { return target_.GetPosition(); }
    const D3DXVECTOR3& GetTargetRotation(void) const { return target_.GetPosition(); }
    const D3DXVECTOR3& GetTargetVelocity(void) const { return target_.GetVelocity(); }

    // set
    void SetAt(const D3DXVECTOR3& at) { camera_.at_ = at; }
    void SetEye(const D3DXVECTOR3& eye) { camera_.eye_ = eye; }

  private:
    // property
    Camera& camera_;
    const ObjectBase& target_;
  };

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
  void AssignCameraSteering(CameraSteering* p_camera_steering);

private:
  // property
  D3DXMATRIX projection_;
  D3DXMATRIX view_;

  D3DXVECTOR3 eye_;
  D3DXVECTOR3 at_;

  CameraSteering* p_camera_steering_;
};

using CameraFactory = liza::generic::Factory<Camera>;
