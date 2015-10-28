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
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Camera;
class ObjectBase;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CameraSteeringFixed {
public:
  // ctor
  CameraSteeringFixed(Camera& camera, ObjectBase& target);

  // dtor
  ~CameraSteeringFixed();

  // Update
  void Update(float elapsed_time);

private:
  Camera& camera_;
  const ObjectBase& target_;
};
