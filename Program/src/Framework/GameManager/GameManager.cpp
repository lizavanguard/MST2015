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

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_config.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/DebugProc/DebugProc.h"
#include "Framework/Effect/EffectManager.h"
#include "Framework/Fade/Fade.h"
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
  : pDebugProc_(nullptr)
  , pInputManager_(nullptr)
  , pSceneManager_(nullptr)
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
  TextureManager::Instance().Load("Game"); // TODO: Game -> Title?
  ModelManager::Instance();
  SoundManager::Instance();
  WiiControllerManager::Instance();

  pDebugProc_ = new DebugProc();
  pDebugProc_->Init(pDevice);
  pInputManager_ = new InputManager(hInstance, hWnd);

  //pSceneManager_ = new SceneManager(new SceneTitle());
  pSceneManager_ = new SceneManager(new SceneGame());

  RenderTargetManager::Instance();

  pEffectManager_ = new EffectManager(pDevice,
                                      SoundManager::Instance().GetXAudio2(),
                                      kFov, kAspect, kNear, kFar,
                                      kWindowWidthF, kWindowHeightF);
  EffectManagerServiceLocator::Provide(pEffectManager_);
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  //delete p_test;
  delete pEffectManager_;
  delete pSceneManager_;
  delete pInputManager_;
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
  auto& camera = CameraManager::Instance().GetMainCamera();
  pEffectManager_->ChangeView(camera._GetEye(), camera._GetAt(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
  pEffectManager_->Update();

  //DebugProc::Print("CONTROLLER1:â¡ë¨ìxX[%.3f]\n", WiiControllerManager::Instance().GetWiiController(0)->getAccelerationX());
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
  pDebugProc_->Draw();
  pEffectManager_->Draw();

  pDevice->EndScene();
  RenderTargetManager::Instance().UnAssign();

  pDevice->BeginScene();

  // TODO: blend

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
