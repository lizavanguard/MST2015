//==============================================================================
//
// ƒQ[ƒ€ŠÇ— [GameManager.cpp]
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

  CameraManager::Instance(); // Initialize

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

  Camera& camera = CameraManager::Instance().GetMainCamera();
  pEffectManager_ = new EffectManager(pDevice,
                                      camera.GetProjectionMatrix(),
                                      camera.GetViewMatrix());
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
  pEffectManager_->SetView(camera.GetViewMatrix());
  pEffectManager_->Update();

  //DebugProc::Print("CONTROLLER1:‰Á‘¬“xX[%.3f]\n", WiiControllerManager::Instance().GetWiiController(0)->getAccelerationX());
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
