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
#include "liza/game/State.hpp"
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
    CameraSteering() {}

    // dtor
    virtual ~CameraSteering() {}

    // Execute
    virtual void Execute(Camera& camera, float elapsed_time) = 0;

  protected:
    // get
    const D3DXVECTOR3& GetAt(const Camera& camera) const { return camera.at_; }
    const D3DXVECTOR3& GetEye(const Camera& camera) const { return camera.eye_; }
    const D3DXVECTOR3& GetTargetPosition(ObjectBase& target) const { return target.GetPosition(); }
    const D3DXVECTOR3& GetTargetRotation(ObjectBase& target) const { return target.GetRotation(); }
    const D3DXVECTOR3& GetTargetSpeed(ObjectBase& target) const { return target.GetSpeed(); }
    const D3DXVECTOR3& GetTargetVelocity(ObjectBase& target) const { return target.GetVelocity(); }

    // set
    void SetAt(Camera& camera, const D3DXVECTOR3& at) { camera.at_ = at; }
    void SetEye(Camera& camera, const D3DXVECTOR3& eye) { camera.eye_ = eye; }
  };

  friend CameraSteering;

  // Null object
  class NullCameraSteeringObject : public CameraSteering {
  public:
    virtual ~NullCameraSteeringObject() {}
    virtual void Execute(Camera&, float) final {};
  };

public:
  // ctor
  Camera(const D3DXVECTOR3& eye, const D3DXVECTOR3& at);

  // dtor
  ~Camera();

  // Assign
  void AssignCameraSteering(CameraSteering* p_camera_steering);

  // Calculate camera-direction
  D3DXVECTOR3 CalculateCameraDirection(void) const {
    D3DXVECTOR3 direction = at_ - eye_;
    return *D3DXVec3Normalize(&direction, &direction);
  }

  // Update
  virtual void Update(float elapsed_time);

  // get
  CameraSteering* GetCameraSteering(void) const { return p_camera_steering_; }
  const D3DXMATRIX& GetViewMatrix(void) const { return view_; }
  const D3DXMATRIX& GetProjectionMatrix(void) const { return projection_; }

  // get
  const D3DXVECTOR3& _GetEye(void) const { return eye_; }
  const D3DXVECTOR3& _GetAt(void) const { return at_; }

  // set
  void _SetEye(const D3DXVECTOR3& eye) { eye_ = eye; }
  void _SetAt(const D3DXVECTOR3& at) { at_ = at; }
  void _SetViewMatrix(const D3DXMATRIX& view) { view_ = view; }
  void _SetProjectionMatrix(const D3DXMATRIX& projection) { projection_ = projection; }
  void OnMatrixAutoUpdate(void) { is_auto_update_ = true; }
  void OffMatrixAutoUpdate(void) { is_auto_update_ = false; }

private:
  // property
  D3DXMATRIX projection_;
  D3DXMATRIX view_;
  D3DXVECTOR3 eye_;
  D3DXVECTOR3 at_;
  CameraSteering* p_camera_steering_;

  bool is_auto_update_;
};

using CameraFactory = liza::generic::Factory<Camera>;
