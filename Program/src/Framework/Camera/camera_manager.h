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
#include "liza/generic/SingletonHolder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Camera;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _CameraManager {
public:
  using CameraHandle = unsigned int;
  static const int none = 4294967295;

private:
  using DataType = Camera*;
  using ContainerType = std::vector<DataType>;
  using HandleContainerType = std::unordered_map<std::string, CameraHandle>;

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
  Camera& FindUsingHandle(CameraHandle camera_handle);

  // Register
  // カメラ名とカメラデータを登録する
  void Register(const char* camera_name, Camera* p_camera);

  // UnRegister
  // カメラ名とカメラデータを抹消する
  void UnRegister(void);

  // Get camera handle
  // カメラのハンドルを取得する
  CameraHandle GetCameraHandle(const char* camera_name) const;
  Camera& GetMainCamera(void) { return *p_main_camera_; }

private:
  void _Register(const char* camera_name, Camera* p_camera);

  ContainerType container_;
  HandleContainerType handle_container_;
  Camera* p_main_camera_;
};

using CameraManager = liza::generic::SingletonHolder<_CameraManager>;
