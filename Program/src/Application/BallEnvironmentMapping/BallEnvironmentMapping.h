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
#include "Application/Pin/BiggestPin.h"
#include "Application/Pin/LanePins.h"
#include "Application/Pin/StandardPins.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameEnvirontMappingDrawer : public CubeTextureForEnvironmentMapping::ObjectDrawer {
public:
  // ctor
  GameEnvirontMappingDrawer(SkyBox& skybox, Stage& stage, StandardPins& stdpin)
    : skybox_(skybox), stage_(stage), stdpin_(stdpin) {
  }

  // dtor
  virtual ~GameEnvirontMappingDrawer() {}

private:
  virtual void _DrawObject(void) override {
    _CameraManager::CameraHandle cube_camera_handle
      = CameraManager::Instance().GetCameraHandle(cube_mapping::kCubeCamera);
    _CameraManager::CameraHandle cube_skybox_camera_handle
      = CameraManager::Instance().GetCameraHandle(cube_mapping::kCubeSkyBoxCamera);

    skybox_.SetCameraHandle(cube_skybox_camera_handle);
    skybox_.DrawAll();
    skybox_.ResetCameraHandle();

    auto main_camera_handle = CameraManager::Instance().GetMainCameraHandle();
    CameraManager::Instance().SetMainCameraUsingHandle(cube_camera_handle);
    stage_.DrawAll();
    stdpin_.DrawAll();
    //bigpin_.DrawAll();
    //if( p_lanepins_ ) {
    //  p_lanepins_->DrawAll();
    //}
    CameraManager::Instance().SetMainCameraUsingHandle(main_camera_handle);
  }

  SkyBox& skybox_;
  Stage& stage_;
  StandardPins& stdpin_;
  //LanePins* p_lanepins_;
};
