//==============================================================================
//
// CameraSteeringControl
// Author: Shimizu Shoji
//
// ���݂̃J�����ʒu����^�[�Q�b�g�̈ʒu��Ǐ]����H
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
class CameraSteeringControl : public Camera::CameraSteering {
public:
  // ctor
  CameraSteeringControl(Camera& camera, ObjectBase& target);

  // dtor
  virtual ~CameraSteeringControl();

  // Update
  virtual void Update(float elapsed_time) override;

private:
  CameraSteeringHoming* p_steering_;
  ObjectBase* p_dummy_;
};
