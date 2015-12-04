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
#include "EffekseerUtility.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const unsigned int k2DEffectMax = 500;
  const unsigned int k3DEffectMax = 1000;
  const unsigned int kEffectMax = k2DEffectMax + k3DEffectMax;
  const unsigned int kMonauralMax = 100;
  const unsigned int kStereoMax = 100;
  const char* k2DStartPath = "./data/Effect/2D";
  const char* k3DStartPath = "./data/Effect/3D";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
EffectManager::EffectManager(LPDIRECT3DDEVICE9 p_device,
                             IXAudio2* p_xaudio,
                             const float fov, const float aspect, const float zn, const float zf,
                             const float width, const float height)
    : p_finder_2d_(nullptr)
    , p_finder_3d_(nullptr)
    , p_manager_3d_(nullptr)
    , p_manager_2d_(nullptr)
    , p_sound_(nullptr)
    , p_renderer_(nullptr)
    , half_width_(0.0f)
    , half_height_(0.0f) {
  view_matrix_2d_.Indentity();
  view_matrix_3d_.Indentity();
  perspective_matrix_.Indentity();
  ortho_matrix_.Indentity();

  p_renderer_ = EffekseerRendererDX9::Renderer::Create(p_device, kEffectMax);
  p_sound_ = EffekseerSound::Sound::Create(p_xaudio, kMonauralMax, kStereoMax);

  p_manager_2d_ = Effekseer::Manager::Create(k2DEffectMax);
  p_manager_2d_->SetSpriteRenderer(p_renderer_->CreateSpriteRenderer());
  p_manager_2d_->SetRibbonRenderer(p_renderer_->CreateRibbonRenderer());
  p_manager_2d_->SetRingRenderer(p_renderer_->CreateRingRenderer());
  p_manager_2d_->SetTextureLoader(p_renderer_->CreateTextureLoader());
  p_manager_2d_->SetSoundPlayer(p_sound_->CreateSoundPlayer());
  p_manager_2d_->SetSoundLoader(p_sound_->CreateSoundLoader());
  p_manager_2d_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

  p_manager_3d_ = Effekseer::Manager::Create(k3DEffectMax);
  p_manager_3d_->SetSpriteRenderer(p_renderer_->CreateSpriteRenderer());
  p_manager_3d_->SetRibbonRenderer(p_renderer_->CreateRibbonRenderer());
  p_manager_3d_->SetRingRenderer(p_renderer_->CreateRingRenderer());
  p_manager_3d_->SetTextureLoader(p_renderer_->CreateTextureLoader());
  p_manager_3d_->SetSoundPlayer(p_sound_->CreateSoundPlayer());
  p_manager_3d_->SetSoundLoader(p_sound_->CreateSoundLoader());
  p_manager_3d_->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

  p_finder_2d_ = new ContainerType(k2DStartPath, [this](const char* p_filename, EffectManager::DataType* pp_effect) {
    unsigned int length = strlen(p_filename) + 1;
    wchar_t p_wfilename[1024];
    mbstowcs_s(&length, p_wfilename, p_filename, strlen(p_filename) + 1);
    *pp_effect = Effekseer::Effect::Create(p_manager_2d_, (const EFK_CHAR*)p_wfilename);
  });

  p_finder_3d_ = new ContainerType(k3DStartPath, [this](const char* p_filename, EffectManager::DataType* pp_effect) {
    unsigned int length = strlen(p_filename) + 1;
    wchar_t p_wfilename[1024];
    mbstowcs_s(&length, p_wfilename, p_filename, strlen(p_filename) + 1);
    *pp_effect = Effekseer::Effect::Create(p_manager_3d_, (const EFK_CHAR*)p_wfilename);
  });

  ChangePerspective(fov, aspect, zn, zf);
  ChangeOrtho(width, height);
  _Create2DView();
}

//------------------------------------------------
// dtor
//------------------------------------------------
EffectManager::~EffectManager() {
  SafeDelete(p_finder_3d_);
  SafeDelete(p_finder_2d_);

  p_manager_3d_->Destroy();
  p_manager_2d_->Destroy();
  p_sound_->Destory();
  p_renderer_->Destory();
}

//------------------------------------------------
// Update
//------------------------------------------------
void EffectManager::Update(void) {
  p_manager_2d_->Update();
  p_manager_3d_->Update();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void EffectManager::Draw(void) {
  _Assign3DView();
  _AssignPerspective();
  p_renderer_->BeginRendering();
  p_manager_3d_->Draw();
  p_renderer_->EndRendering();

  _Assign2DView();
  _AssignOrtho();
  p_renderer_->BeginRendering();
  p_manager_2d_->Draw();
  p_renderer_->EndRendering();
}

//------------------------------------------------
// Play Effect
//------------------------------------------------
EffectManager::HandleType EffectManager::Play2D(const char* effect_name, const float x, const float y) {
  Effekseer::Effect* p_effect = _Find2D(effect_name);
  return p_manager_2d_->Play(p_effect, x - half_width_, half_height_ - y, 0.0f);
}

EffectManager::HandleType EffectManager::Play3D(const char* effect_name, const float x, const float y, const float z) {
  Effekseer::Effect* p_effect = _Find3D(effect_name);
  return p_manager_3d_->Play(p_effect, x, y, z);
}

//------------------------------------------------
// Change
//------------------------------------------------
void EffectManager::ChangeView(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up) {
  view_matrix_3d_.LookAtLH(EffekseerUtility::VectorToEffekSeer(eye),
                           EffekseerUtility::VectorToEffekSeer(at),
                           EffekseerUtility::VectorToEffekSeer(up));
}

void EffectManager::ChangeOrtho(const float width, const float height) {
  ortho_matrix_.OrthographicLH(width, height, 0.1f, 10.0f);
  half_width_ = width * 0.5f;
  half_height_ = height * 0.5f;
}

void EffectManager::ChangePerspective(const float fov, const float aspect, const float zn, const float zf) {
  perspective_matrix_.PerspectiveFovLH(fov, aspect, zn, zf);
}

//------------------------------------------------
// set
//------------------------------------------------
// for 2d
void EffectManager::SetScreenPosition(const HandleType handle, const D3DXVECTOR2& position) {
  SetScreenPosition(handle, position.x, position.y);
}

void EffectManager::SetScreenPosition(const HandleType handle, const float x, const float y) {
  p_manager_2d_->SetLocation(handle, x - half_width_, half_height_ - y, 0.0f);
}

void EffectManager::SetScreenScale(const HandleType handle, const D3DXVECTOR2& scale) {
  SetScreenScale(handle, scale.x, scale.y);
}

void EffectManager::SetScreenScale(const HandleType handle, const float x, const float y) {
  p_manager_2d_->SetScale(handle, x, y, 1.0f);
}

// for 3d
void EffectManager::SetPosition(const HandleType handle, const D3DXVECTOR3& position) {
  SetPosition(handle, position.x, position.y, position.z);
}

void EffectManager::SetPosition(const HandleType handle, const float x, const float y, const float z) {
  p_manager_3d_->SetLocation(handle, x, y, z);
}

void EffectManager::SetRotation(const HandleType handle, const D3DXVECTOR3& axis, const float angle) {
  p_manager_3d_->SetRotation(handle, Effekseer::Vector3D(axis.x, axis.y, axis.z), angle);
}

void EffectManager::SetScale(const HandleType handle, const D3DXVECTOR3& scale) {
  SetScale(handle, scale.x, scale.y, scale.z);
}

void EffectManager::SetScale(const HandleType handle, const float x, const float y, const float z) {
  p_manager_3d_->SetScale(handle, x, y, z);
}

//------------------------------------------------
// Find
//------------------------------------------------
EffectManager::DataType EffectManager::_Find2D(const ContainerType::KeyType& effect_name) {
  return p_finder_2d_->Find(effect_name);
}

EffectManager::DataType EffectManager::_Find3D(const ContainerType::KeyType& effect_name) {
  return p_finder_3d_->Find(effect_name);
}

//------------------------------------------------
// Assign
//------------------------------------------------
void EffectManager::_Assign2DView(void) {
  p_renderer_->SetCameraMatrix(view_matrix_2d_);
}

void EffectManager::_Assign3DView(void) {
  p_renderer_->SetCameraMatrix(view_matrix_3d_);
}

void EffectManager::_AssignOrtho(void) {
  p_renderer_->SetProjectionMatrix(ortho_matrix_);
}

void EffectManager::_AssignPerspective(void) {
  p_renderer_->SetProjectionMatrix(perspective_matrix_);
}

//------------------------------------------------
// Create
//------------------------------------------------
void EffectManager::_Create2DView(void) {
  view_matrix_2d_.LookAtLH(Effekseer::Vector3D(0.0f, 0.0f, -1.0f),
                           Effekseer::Vector3D(0.0f, 0.0f,  0.0f),
                           Effekseer::Vector3D(0.0f, 1.0f,  0.0f));
}
