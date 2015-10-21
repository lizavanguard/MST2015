//==============================================================================
//
// _CameraManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera.h"
#include "liza/generic/SingletonHolder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _CameraManager {
private:
  using ContainerType = std::vector<Camera*>;

public:
  // ctor
  _CameraManager();

  // dtor
  ~_CameraManager() {
    for (auto p_camera : container_) {
      SafeDelete(p_camera);
    }
  }

  // Update
  void Update(float elapsed_time) {
    for (auto p_camera : container_) {
      p_camera->Update(elapsed_time);
    }
  }

  // get camera
  Camera& GetCamera(unsigned int index);

  // Push
  void PushCamera(Camera* p_camera);

private:
  ContainerType container_;
};

using CameraManager = liza::generic::SingletonHolder<_CameraManager>;
