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
  CameraSteeringFixed(Camera& camera, ObjectBase& target);

  // dtor
  virtual ~CameraSteeringFixed();

  // Update
  virtual void Update(float elapsed_time) override;
};
