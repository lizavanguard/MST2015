//==============================================================================
//
// ObjectSkyBoxFace
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/factory.hpp"

#include "Framework/Camera/camera_manager.h"

#include "object3d.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectSkyBoxFace : public Object3D {
public:
  // ctor
  ObjectSkyBoxFace(const char* p_filename);

  // dtor
  virtual ~ObjectSkyBoxFace();

private:
  // virtual function
  virtual void _Draw(void) override;

  _CameraManager::CameraHandle skybox_camera_handle_;
};

using ObjectSkyBoxFactory = liza::generic::Factory<ObjectSkyBoxFace>;
