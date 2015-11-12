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
#include "Framework/Shader/shader_manager.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Input/InputManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Model/model_manager.h"
#include "Framework/Utility/DeviceHolder.h"

// HACK:
#include "Application/Test/Test.h"

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
  , pTest_(nullptr)
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

  pTest_ = new Test();
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
  SafeDelete(pTest_);
  delete pInputManager_;
  pDebugProc_->Uninit();
  delete pDebugProc_;
}


//------------------------------------------------
// update
//------------------------------------------------
void GameManager::Update(const float elpasedTime) {
  pInputManager_->Update();
  CameraManager::Instance().Update(elpasedTime);

  pTest_->Update();
}


//------------------------------------------------
// draw
//------------------------------------------------
void GameManager::Draw(void) {
  pTest_->Draw();

  pDebugProc_->Draw();
}