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

#include "liza/generic/ServiceLocator.hpp"

#include "Framework/Utility/DataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// link lib
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#if _DEBUG
#pragma comment(lib, "lib/Debug/Effekseer.lib")
#pragma comment(lib, "lib/Debug/EffekseerRendererDX9.lib")
#else
#pragma comment(lib, "lib/Release/Effekseer.lib")
#pragma comment(lib, "lib/Release/EffekseerRendererDX9.lib")
#endif  // _DEBUG

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class EffectManager {
public:
  using DataType = Effekseer::Effect*;
  using HandleType = Effekseer::Handle;
private:
  using ContainerType = DataLoader<DataType>;

public:
  // ctor
  EffectManager(LPDIRECT3DDEVICE9 p_device, const D3DXMATRIX& perspective, const D3DXMATRIX& ortho);

  // dtor
  ~EffectManager();

  // Update
  void Update(void);

  // Draw
  void Draw(void);

  // Play
  HandleType Play(const char* p_effect_name, float x, float y, float z);

  // set
  void SetPosition(HandleType handle, const D3DXVECTOR3& position);
  void SetPosition(HandleType handle, float x, float y, float z);
  void SetRotation(HandleType handle, const D3DXVECTOR3& axis, float angle);
  void SetView(const D3DXMATRIX& view);
  void SetOrtho(const D3DXMATRIX& ortho);
  void SetPerspective(const D3DXMATRIX& perspective);

private:
  DataType _Find(const ContainerType::KeyType& effect_name);

  ContainerType* p_finder_;
  Effekseer::Manager* p_manager_;
  EffekseerSound::Sound* p_sound_;
  EffekseerRendererDX9::Renderer* p_renderer_;
  Effekseer::Matrix44 view_matrix_;
  Effekseer::Matrix44 projection_matrix_;
  Effekseer::Matrix44 ortho_matrix_;
};

using EffectManagerServiceLocator = liza::generic::ServiceLocator<EffectManager>;
