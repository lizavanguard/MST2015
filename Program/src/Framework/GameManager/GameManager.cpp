//==============================================================================
//
// ÉQÅ[ÉÄä«óù [GameManager.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameManager.h"

#include "liza/game/DirectXUtility/DirectXUtility.h"

#include "Framework/AlphaObject/AlphaObjectManager.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_config.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/DebugProc/DebugProc.h"
#include "Framework/Effect/EffectManager.h"
#include "Framework/Fade/Fade.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Light/light.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Model/model_manager.h"
#include "Framework/RenderTarget/RenderTargetManager.h"
#include "Framework/Utility/DeviceHolder.h"

// HACK:
#include "Application/Title/SceneTitle.h"
#include "Application/Game/SceneGame.h"
#include "Application/Result/SceneResult.h"
#include "Application/ScoreHolder/ScoreHolder.h"
#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Get Instance
//------------------------------------------------
GameManager& GameManager::Instance(HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice) {
  static GameManager instance(hInstance, hWnd, pDevice);
  return instance;
}


//------------------------------------------------
// ctor
//------------------------------------------------
GameManager::GameManager(HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
  : pAlphaObjectManager_(nullptr)
  , pDebugProc_(nullptr)
  , pHudManager_(nullptr)
  , pInputManager_(nullptr)
  , pSceneManager_(nullptr)
  , pScoreHolder_(nullptr)
  , pLight_(nullptr)
{
  DeviceHolder::Instance().SetDevice(pDevice);

  auto& camera_manager = CameraManager::Instance(); // Initialize
  for (int i = 0; i < 3; ++i) {
    Camera* p_main_camera = CameraFactory::Create(kInitialEyePosition[i], kInitialAtPosition[i]);
    p_main_camera->Update(0);
    camera_manager.Register(kCameraName[i], p_main_camera);
  }
  camera_manager.SetMainCamera(kCameraName[0]);
  // create a skybox camera
  Camera& main_camera = camera_manager.GetMainCamera();
  D3DXVECTOR3 at = main_camera.CalculateCameraDirection();
  D3DXVECTOR3 eye(-at);
  Camera* p_camera = new Camera(eye, at);
  camera_manager.Register(kSkyboxCameraName, p_camera);

  ShaderManager::Instance();
  TextureManager::Instance().Load("General");
  TextureManager::Instance().Load("Model");
  ModelManager::Instance();
  SoundManager::Instance();
  WiiControllerManager::Instance();

  pDebugProc_ = new DebugProc();
  pDebugProc_->Init(pDevice);
  pInputManager_ = new InputManager(hInstance, hWnd);

  RenderTargetManager::Instance();

  pEffectManager_ = new EffectManager(pDevice,
                                      SoundManager::Instance().GetXAudio2(),
                                      kFov, kAspect, kNear, kFar,
                                      kWindowWidthF, kWindowHeightF);
  EffectManagerServiceLocator::Provide(pEffectManager_);

  pLight_ = new Light();
  LightServiceLocator::Provide(pLight_);

  pAlphaObjectManager_ = new AlphaObjectManager();
  AlphaObjectServiceLocator::Provide(pAlphaObjectManager_);

  pHudManager_ = new HudManager();
  HudServiceLocator::Provide(pHudManager_);

  pScoreHolder_ = new ScoreHolder();
  ScoreHolderServiceLocator::Provide(pScoreHolder_);

  pSceneManager_ = new SceneManager(new SceneGame());
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  //delete p_test;
  delete pScoreHolder_;
  delete pLight_;
  delete pSceneManager_;
  delete pHudManager_;
  delete pAlphaObjectManager_;
  delete pInputManager_;
  delete pEffectManager_;
  pDebugProc_->Uninit();
  delete pDebugProc_;
}


//------------------------------------------------
// update
//------------------------------------------------
void GameManager::Update(const float elapsedTime) {
  WiiControllerManager::Instance().Update();
  pInputManager_->Update();
  CameraManager::Instance().Update(elapsedTime);

  pSceneManager_->Update(elapsedTime);
  pAlphaObjectManager_->Update(elapsedTime);
  pHudManager_->Update(elapsedTime);

  auto& camera = CameraManager::Instance().GetMainCamera();
  pEffectManager_->ChangeView(camera._GetEye(), camera._GetAt(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
  pEffectManager_->Update();
}


//------------------------------------------------
// draww
//------------------------------------------------
void GameManager::Draw(void) {
  auto pDevice = DeviceHolder::Instance().GetDevice();

  pDevice->EndScene();

  RenderTargetManager::Instance().Assign();
  RenderTargetManager::Instance().Clear();
  pDevice->BeginScene();

  pSceneManager_->Draw();
  pEffectManager_->Draw3D();
  pAlphaObjectManager_->Draw();
  pHudManager_->Draw();
  pDevice->EndScene();

  pDevice->Clear(
    0,
    nullptr,
    (D3DCLEAR_ZBUFFER),	// ÉÇÅ[Éh
    D3DCOLOR_RGBA(0, 128, 128, 0),	// îwåiêF
    1.0f,		// Zê[ìx
    0
    );

  pDevice->BeginScene();
  pEffectManager_->Draw2D();
  pHudManager_->DrawAlphaHud();
  pDebugProc_->Draw();
  pDevice->EndScene();
  RenderTargetManager::Instance().UnAssign();

  pDevice->BeginScene();

  // Fade
  pDevice->SetTexture(0, RenderTargetManager::Instance().GetTexture(0));
  auto p_shader = ShaderManager::Instance().FindShader("fade");

  p_shader->SetFloat("u_fade_value", GetAlpha());
  p_shader->SetTexture("texture_decale", RenderTargetManager::Instance().GetTexture(0));
  p_shader->Begin(nullptr, 0);
  p_shader->BeginPass(0);
  DrawFullScreenQuad(pDevice, 0, 0, 1, 1);
  pDevice->SetTexture(0, nullptr);
  p_shader->EndPass();
  p_shader->End();
}
