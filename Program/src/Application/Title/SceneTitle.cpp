//==============================================================================
//
// SceneTitle
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneTitle.h"

#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"
#include "Framework/Texture/texture_manager.h"

#include "window_config.h"

#include "Application/Game/SceneGameFactory.h"
#include "Application/Title/PushStartButton/PushStartButton.h"


//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTextureGroupName = "Title";
}
//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneTitle::SceneTitle() : p_root_(nullptr) {
  TextureManager::Instance().Load(kTextureGroupName);

  p_root_ = RootFactory::Create();

  p_root_->AttachChild(Object2DFactory::Create("Title/logo", D3DXVECTOR3(kWindowWidth * 0.5f, 200.0f, 0.0f), D3DXVECTOR2(800.0f, 300.0f)));
  p_root_->AttachChild(Object2DFactory::Create("Title/push_start", D3DXVECTOR3(640.0f, 450.0f, 0.0f), D3DXVECTOR2(600.0f, 200.0f), new Object2DSteeringFlashing()));
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneTitle::~SceneTitle() {
  Root::Destroy(p_root_);

  TextureManager::Instance().Unload(kTextureGroupName);
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneTitle::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  }

  p_root_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneTitle::_Draw(void) {
  p_root_->DrawAll();
}
