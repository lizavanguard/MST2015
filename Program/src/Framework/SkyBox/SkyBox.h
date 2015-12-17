//==============================================================================
//
// SkyBox
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_base.h"

#include "Framework/Camera/camera_manager.h"

#include "liza/generic/factory.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CameraSteeringSet;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SkyBox : public ObjectBase {
public:
  // ctor
  SkyBox();

  // dtor
  virtual ~SkyBox();

  // Reset
  void ResetCameraHandle(void);

  // set
  void SetCameraHandle(_CameraManager::CameraHandle camera_handle);

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  CameraSteeringSet* p_camera_steering_;
};

using SkyBoxFactory = liza::generic::Factory<SkyBox>;
