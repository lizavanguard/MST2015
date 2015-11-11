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
  using DataType = Camera*;
  using CameraHandle = unsigned int;
  using ContainerType = std::vector<DataType>;
  using HandleContainerType = std::unordered_map<std::string, CameraHandle>;

  static const int none = 4294967295;

public:
  // ctor
  _CameraManager();

  // dtor
  ~_CameraManager();

  // Update
  void Update(float elapsed_time);

  // Find
  // カメラを検索する
  Camera& Find(const char* camera_name);
  Camera& Find(CameraHandle camera_handle);

  // Register
  // カメラ名とカメラデータを登録する
  void Register(const char* camera_name, Camera* p_camera);

  // UnRegister
  // カメラ名とカメラデータを抹消する
  void UnRegister(void);

  // Get camera handle
  // カメラのハンドルを取得する
  CameraHandle GetCameraHandle(const char* camera_name) const;

private:
  ContainerType container_;
  HandleContainerType handle_container_;
};

using CameraManager = liza::generic::SingletonHolder<_CameraManager>;
