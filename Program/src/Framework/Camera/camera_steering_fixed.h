//==============================================================================
//
// CameraSteeringFixed
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
