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

#include "Framework/Camera/camera_manager.h"
#include "Framework/DebugProc/DebugProc.h"
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

#include "liza/game/DirectXUtility/DirectXUtility.h"

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

  pDebugProc_ = new DebugProc();
  pDebugProc_->Init(pDevice);
  pInputManager_ = new InputManager(hInstance, hWnd);

  //pSceneManager_ = new SceneManager(new SceneTitle());
  pSceneManager_ = new SceneManager(new SceneGame());

  RenderTargetManager::Instance();
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  delete pSceneManager_;
  delete pInputManager_;
  pDebugProc_->Uninit();
  delete pDebugProc_;
}


//------------------------------------------------
// update
//------------------------------------------------
void GameManager::Update(const float elapsedTime) {
  pInputManager_->Update();
  CameraManager::Instance().Update(elapsedTime);

  pSceneManager_->Update(elapsedTime);
}


//------------------------------------------------
// draw
//------------------------------------------------
void GameManager::Draw(void) {
  auto pDevice = DeviceHolder::Instance().GetDevice();

  pDevice->EndScene();
  RenderTargetManager::Instance().Assign();
  RenderTargetManager::Instance().Clear();
  pDevice->BeginScene();

  pSceneManager_->Draw();
  pDebugProc_->Draw();

  pDevice->EndScene();
  RenderTargetManager::Instance().UnAssign();
  pDevice->BeginScene();

  // TODO: blend
  pDevice->SetTexture(0, RenderTargetManager::Instance().GetTexture(0));
  DrawFullScreenQuad(pDevice, 0, 0, 1, 1);
  pDevice->SetTexture(0, nullptr);
}
