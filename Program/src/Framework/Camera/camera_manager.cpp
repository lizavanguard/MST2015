//==============================================================================
//
// _CameraManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "camera_manager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_CameraManager::_CameraManager() {
  // TODO:
  //static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 10.0f, -15.0f};
  static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 75.0f, -40.0f};
  PushCamera(CameraFactory::Create(kInitialEyePosition, D3DXVECTOR3(0, 0, 0)));
}

//------------------------------------------------
// Get Camera
//------------------------------------------------
Camera& _CameraManager::GetCamera(const unsigned int index) {
   return *container_[index];
 }

//------------------------------------------------
// Push
//------------------------------------------------
void _CameraManager::PushCamera(Camera* p_camera) {
  container_.push_back(p_camera);
}
