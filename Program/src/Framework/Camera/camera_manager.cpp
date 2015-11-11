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
_CameraManager::_CameraManager() {
}

//------------------------------------------------
// dtor
//------------------------------------------------
_CameraManager::~_CameraManager() {
  UnRegister();
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
// �J��������������
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
// �J�������ƃJ�����f�[�^��o�^����
//------------------------------------------------
void _CameraManager::Register(const char* camera_name, Camera* p_camera) {
  unsigned int num = container_.size();
  container_.push_back(p_camera);
  handle_container_.insert(std::make_pair(camera_name, num));
}

//------------------------------------------------
// UnRegister
// �J�������ƃJ�����f�[�^�𖕏�����
//------------------------------------------------
void _CameraManager::UnRegister(void) {
  for (auto p_camera : container_) {
    SafeDelete(p_camera);
  }

  container_.clear();
  handle_container_.clear();
}

//------------------------------------------------
// Get camera handle
// �J�����̃n���h�����擾����
//------------------------------------------------
_CameraManager::CameraHandle _CameraManager::GetCameraHandle(const char* camera_name) const {
  auto it = handle_container_.find(camera_name);
  MY_BREAK_ASSERT(it != handle_container_.end());
  return it->second;
}
