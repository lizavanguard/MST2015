//==============================================================================
//
// GameEnvirontMappingDrawer
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/CubeTextureForEnvironmentMapping/CubeTextureForEnvironmentMapping.h"
#include "Framework/SkyBox/SkyBox.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"

#include "Application/Stage/Stage.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameEnvirontMappingDrawer : public CubeTextureForEnvironmentMapping::ObjectDrawer {
public:
  // ctor
  GameEnvirontMappingDrawer(SkyBox& skybox, Stage& stage) : skybox_(skybox), stage_(stage) {
  }

  // dtor
  virtual ~GameEnvirontMappingDrawer() {}

private:
  virtual void _DrawObject(void) override {
    _CameraManager::CameraHandle cube_camera_handle = CameraManager::Instance().GetCameraHandle(cube_mapping::kCubeCamera);
    auto main_camera_handle = CameraManager::Instance().GetMainCameraHandle();
    CameraManager::Instance().SetMainCameraUsingHandle(cube_camera_handle);

    skybox_.SetCameraHandle(cube_camera_handle);
    skybox_.DrawAll();
    stage_.DrawAll();
    skybox_.ResetCameraHandle();

    CameraManager::Instance().SetMainCameraUsingHandle(main_camera_handle);
  }

  SkyBox& skybox_;
  Stage& stage_;
};
