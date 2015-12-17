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
#include "camera.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_CameraManager::_CameraManager() : p_main_camera_(nullptr), handle_main_camera_(0) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
_CameraManager::~_CameraManager() {
  UnRegisterAll();
}

//------------------------------------------------
// Update
//------------------------------------------------
void _CameraManager::Update(const float elapsed_time) {
  for (auto p_camera : container_) {
    p_camera->Update(elapsed_time);
  }
}

//------------------------------------------------
// Find
// カメラを検索する
//------------------------------------------------
Camera& _CameraManager::Find(const char* camera_name) {
  return *_Find(camera_name);
}

Camera& _CameraManager::FindUsingHandle(const CameraHandle camera_handle) {
  return *_FindUsingHandle(camera_handle);
}

//------------------------------------------------
// Register
// カメラ名とカメラデータを登録する
//------------------------------------------------
void _CameraManager::Register(const char* camera_name, Camera* p_camera) {
  _Register(camera_name, p_camera);
}

////------------------------------------------------
//// UnRegister
//// カメラ名とカメラデータを抹消する
////------------------------------------------------
//void _CameraManager::UnRegister(const char* camera_name) {
//  auto it = handle_container_.find(camera_name);
//  if (it == handle_container_.end()) {
//    MY_BREAK_ASSERT(false);
//    return;
//  }
//  SafeDelete(container_[it->second]);
//  container_.
//  handle_container_.erase(it);
//}

void _CameraManager::UnRegisterAll(void) {
  for (auto p_camera : container_) {
    SafeDelete(p_camera);
  }
}

//------------------------------------------------
// Get camera handle
// カメラのハンドルを取得する
//------------------------------------------------
_CameraManager::CameraHandle _CameraManager::GetCameraHandle(const char* camera_name) const {
  auto it = handle_container_.find(camera_name);
  MY_BREAK_ASSERT(it != handle_container_.end());
  return it->second;
}

//------------------------------------------------
// Set MainCamera
//------------------------------------------------
void _CameraManager::SetMainCamera(const char* camera_name) {
  handle_main_camera_ = _FindHandle(camera_name);
  p_main_camera_ = _FindUsingHandle(handle_main_camera_);
}

void _CameraManager::SetMainCameraUsingHandle(const CameraHandle camera_handle) {
  handle_main_camera_ = camera_handle;
  p_main_camera_ = _FindUsingHandle(camera_handle);
}

//------------------------------------------------
// _Find
//------------------------------------------------
Camera* _CameraManager::_Find(const char* camera_name) {
  return container_[_FindHandle(camera_name)];
}

_CameraManager::CameraHandle _CameraManager::_FindHandle(const char* camera_name) {
  auto it = handle_container_.find(camera_name);
  MY_BREAK_ASSERT(it != handle_container_.end());
  return it->second;
}

Camera* _CameraManager::_FindUsingHandle(const CameraHandle camera_handle) {
  return container_[camera_handle];
}

//------------------------------------------------
// _register
//------------------------------------------------
void _CameraManager::_Register(const char* camera_name, Camera* p_camera) {
  unsigned int num = container_.size();
  container_.push_back(p_camera);
  handle_container_.insert(std::make_pair(camera_name, num));
}
