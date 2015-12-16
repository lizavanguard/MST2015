//==============================================================================
//
// CameraSteeringMoving
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
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CameraSteeringHoming;
class ObjectBase;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CameraSteeringMoving : public Camera::CameraSteering {
public:
  // ctor
  CameraSteeringMoving(const D3DXVECTOR3& position_a, const D3DXVECTOR3& position_b, float time);

  // dtor
  virtual ~CameraSteeringMoving();

  // Execute
  virtual void Execute(Camera& camera, float elapsed_time) override;

private:
  CameraSteeringHoming* p_steering_;
  ObjectBase* p_dummy_;
};
