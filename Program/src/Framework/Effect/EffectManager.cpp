//==============================================================================
//
// EffectManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "EffectManager.h"
#include "EffekSeerUtility.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const unsigned int kEffectMax = 2000;
  const char* kStartPath = "./data/Effect";
}

Effekseer::Effect* p_effect = nullptr;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
EffectManager::EffectManager(LPDIRECT3DDEVICE9 p_device,
                             const float fov, const float aspect, const float zn, const float zf)
    : p_finder_(nullptr)
    , p_manager_(nullptr)
    , p_sound_(nullptr)
    , p_renderer_(nullptr) {
  p_renderer_ = EffekseerRendererDX9::Renderer::Create(p_device, kEffectMax);
  //p_sound_ = EffekseerSound::Sound::Create(IXAudio2*, モノラル再生用ボイス数, ステレオ再生用ボイス数);
  p_manager_ = Effekseer::Manager::Create(kEffectMax);

  p_manager_->SetSpriteRenderer(p_renderer_->CreateSpriteRenderer());
  p_manager_->SetRibbonRenderer(p_renderer_->CreateRibbonRenderer());
  p_manager_->SetRingRenderer(p_renderer_->CreateRingRenderer());

  p_manager_->SetTextureLoader(p_renderer_->CreateTextureLoader());
  //p_manager_->SetSoundPlayer(sound->CreateSoundPlayer());
  //p_manager_->SetSoundLoader(sound->CreateSoundLoader());

  p_manager_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

  p_finder_ = new ContainerType(kStartPath, [this](const char* p_filename, EffectManager::DataType* pp_effect) {
    unsigned int length = strlen(p_filename) + 1;
    wchar_t p_wfilename[1024];
    mbstowcs_s(&length, p_wfilename, p_filename, strlen(p_filename) + 1);
    *pp_effect = Effekseer::Effect::Create(p_manager_, (const EFK_CHAR*)p_wfilename);
  });

  ChangePerspective(fov, aspect, zn, zf);

  //p_effect = Effekseer::Effect::Create(p_manager_, (const EFK_CHAR*)(L"./data/Effect/b_square.efk"));
  //p_manager_->Play(p_effect, 0, 0, 0);
}

//------------------------------------------------
// dtor
//------------------------------------------------
EffectManager::~EffectManager() {
  p_manager_->Destroy();
  //p_sound_->Destory();
  p_renderer_->Destory();

  SafeDelete(p_finder_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void EffectManager::Update(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up) {
  ChangeLookAt(eye, at, up);

  p_renderer_->SetCameraMatrix(view_matrix_);
  p_renderer_->SetProjectionMatrix(projection_matrix_);

  // 3Dサウンド用リスナー設定の更新
  //p_sound_->SetListener(リスナー位置, 注目点, 上方向ベクトル);

  p_manager_->Update();
}
#include "Framework/Utility/DeviceHolder.h"
//------------------------------------------------
// Draw
//------------------------------------------------
void EffectManager::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  p_renderer_->BeginRendering();
  p_manager_->Draw();
  p_renderer_->EndRendering();
  p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//------------------------------------------------
// Change
//------------------------------------------------
void EffectManager::ChangeLookAt(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up) {
  view_matrix_.LookAtLH(EffekSeerUtility::VectorToEffekSeer(eye),
                        EffekSeerUtility::VectorToEffekSeer(at),
                        EffekSeerUtility::VectorToEffekSeer(up));
}

void EffectManager::ChangePerspective(const float fov, const float aspect, const float zn, const float zf) {
  projection_matrix_.PerspectiveFovLH(fov, aspect, zn, zf);
}

//------------------------------------------------
// Play Effect
//------------------------------------------------
EffectManager::HandleType EffectManager::Play(const char* effect_name, const float x, const float y, const float z) {
  Effekseer::Effect* p_effect = _Find(effect_name);
  return p_manager_->Play(p_effect, x, y, z);
}

//------------------------------------------------
// set
//------------------------------------------------
void EffectManager::SetPosition(const HandleType handle, const D3DXVECTOR3& position) {
  SetPosition(handle, position.x, position.y, position.z);
}

void EffectManager::SetPosition(const HandleType handle, const float x, const float y, const float z) {
  p_manager_->SetLocation(handle, x, y, z);
}

void EffectManager::SetRotation(const HandleType handle, const D3DXVECTOR3& axis, const float angle) {
  p_manager_->SetRotation(handle, Effekseer::Vector3D(axis.x, axis.y, axis.z), angle);
}

//------------------------------------------------
// Find
//------------------------------------------------
EffectManager::DataType EffectManager::_Find(const ContainerType::KeyType& effect_name) {
  return p_finder_->Find(effect_name);
}
