//==============================================================================
//
// EffectManager
// Author: Shimizu Shoji
//
// TODO:
//  Manager等を全部移す
//  Singleton -> ServiceLocator
//  文字列探索が気になったら、ハンドルを追加する（エフェクトの再生ハンドルとは異なる
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#include "EffekseerUtility.h"

#include "liza/generic/ServiceLocator.hpp"

#include "Framework/Utility/DataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// link lib
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#if _DEBUG
#pragma comment(lib, "lib/Debug/Effekseer.lib")
#pragma comment(lib, "lib/Debug/EffekseerRendererDX9.lib")
#pragma comment(lib, "lib/Debug/EffekseerSoundXAudio2.lib")
#else
#pragma comment(lib, "lib/Release/Effekseer.lib")
#pragma comment(lib, "lib/Release/EffekseerRendererDX9.lib")
#pragma comment(lib, "lib/Release/EffekseerSoundXAudio2")
#endif  // _DEBUG

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class EffectManager {
public:
  // alias
  using DataType = Effekseer::Effect*;
  using HandleType = Effekseer::Handle;
  using RemovingCallbackFunction = void(*)(void);

private:
  // template struct
  template<typename T>
  struct _UsingEffekseerRelease {
    static void Destroy(T data) {
      ES_SAFE_RELEASE(data);
    }
  };
  using ContainerType = DataLoader<DataType, _UsingEffekseerRelease>;

public:
  // const
  static const HandleType kNullHandle = -1;

  // struct
  struct Handle2D {
    Handle2D() : handle_(0) {}
    explicit Handle2D(Effekseer::Handle handle) : handle_(handle) {}
    HandleType handle_;
  };
  struct Handle3D {
    Handle3D() : handle_(0) {}
    explicit Handle3D(Effekseer::Handle handle) : handle_(handle) {}
    HandleType handle_;
  };

public:
  // ctor
  // Perspective = fov, aspect, zn, zf
  // Ortho = width, height
  EffectManager(
    LPDIRECT3DDEVICE9 p_device,
    IXAudio2* p_xaudio,
    float fov, float aspect, float zn, float zf,
    float width, float height);

  // dtor
  ~EffectManager();

  // Update
  void Update(void);

  // Draw
  void Draw2D(void);
  void Draw3D(void);

  // Play
  Handle2D Play2D(const char* p_effect_name, float x, float y);
  Handle3D Play3D(const char* p_effect_name, float x, float y, float z);

  // Stop
  void Stop2D(Handle2D handle);
  void Stop3D(Handle3D handle);

  // Change
  void ChangeView(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up);
  void ChangeOrtho(float width, float height);
  void ChangePerspective(float fov, float aspect, float zn, float zf);

  // get
  bool IsExits2D(Handle2D handle) const;
  bool IsExits3D(Handle3D handle) const;

  // set
  void SetRemovingCallbackFunction2D(Handle2D handle, RemovingCallbackFunction callback);
  void SetRemovingCallbackFunction3D(Handle3D handle, RemovingCallbackFunction callback);

  // for 2d
  void SetScreenPosition(Handle2D handle, const D3DXVECTOR2& position);
  void SetScreenPosition(Handle2D handle, float x, float y);
  void SetScreenScale(Handle2D handle, const D3DXVECTOR2& scale);
  void SetScreenScale(Handle2D handle, float x, float y);

  // for 3d
  void SetPosition(Handle3D handle, const D3DXVECTOR3& position);
  void SetPosition(Handle3D handle, float x, float y, float z);
  void SetRotation(Handle3D handle, const D3DXVECTOR3& axis, float angle);
  void SetScale(Handle3D handle, const D3DXVECTOR3& scale);
  void SetScale(Handle3D handle, float x, float y, float z);

private:
  // _func
  DataType _Find2D(const ContainerType::KeyType& effect_name);
  DataType _Find3D(const ContainerType::KeyType& effect_name);
  void _Assign2DView(void);
  void _Assign3DView(void);
  void _AssignOrtho(void);
  void _AssignPerspective(void);
  void _Create2DView(void);
  void _SetRemovingCallbackFunction(Effekseer::Manager& manager, HandleType handle, RemovingCallbackFunction callback);

  // property
  ContainerType* p_finder_2d_;
  ContainerType* p_finder_3d_;
  Effekseer::Manager* p_manager_2d_;
  Effekseer::Manager* p_manager_3d_;
  EffekseerSound::Sound* p_sound_;
  EffekseerRendererDX9::Renderer* p_renderer_;
  Effekseer::Matrix44 view_matrix_3d_;
  Effekseer::Matrix44 view_matrix_2d_;
  Effekseer::Matrix44 perspective_matrix_;
  Effekseer::Matrix44 ortho_matrix_;
  float half_width_;
  float half_height_;

  static std::unordered_map<Effekseer::Handle, void(*)(void)> s_function_map_;
};

using EffectManagerServiceLocator = liza::generic::ServiceLocator<EffectManager>;
