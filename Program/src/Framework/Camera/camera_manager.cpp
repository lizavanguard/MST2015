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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kMainCameraName = "MainCamera";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_CameraManager::_CameraManager() {
  static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 75.0f, -101.0f};
  p_main_camera_ = CameraFactory::Create(kInitialEyePosition, D3DXVECTOR3(0, 0, 0));
  p_main_camera_->Update(0);
  _Register(kMainCameraName, p_main_camera_);
}

//------------------------------------------------
// dtor
//------------------------------------------------
_CameraManager::~_CameraManager() {
  UnRegister();
  SafeDelete(p_main_camera_);
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
  auto it = handle_container_.find(camera_name);
  MY_BREAK_ASSERT(it != handle_container_.end());
  return *container_[it->second];
}

Camera& _CameraManager::FindUsingHandle(const CameraHandle camera_handle) {
  return *container_[camera_handle];
}

//------------------------------------------------
// Register
// カメラ名とカメラデータを登録する
//------------------------------------------------
void _CameraManager::Register(const char* camera_name, Camera* p_camera) {
  if (std::string(camera_name).compare(kMainCameraName) == 0) {
    std::string temp = kMainCameraName;
    temp += "は使用できません";
    MY_BREAK_ASSERTMSG(false, temp.c_str());
    return;
  }

  _Register(camera_name, p_camera);
}

//------------------------------------------------
// UnRegister
// カメラ名とカメラデータを抹消する
//------------------------------------------------
void _CameraManager::UnRegister(void) {
  Camera* p_temp = container_[0];

  for (auto it = ++container_.begin(); it != container_.end(); ++it) {
    SafeDelete(*it);
  }

  container_.clear();
  handle_container_.clear();

  _Register(kMainCameraName, p_temp);
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
// _register
//------------------------------------------------
void _CameraManager::_Register(const char* camera_name, Camera* p_camera) {
  unsigned int num = container_.size();
  container_.push_back(p_camera);
  handle_container_.insert(std::make_pair(camera_name, num));
}