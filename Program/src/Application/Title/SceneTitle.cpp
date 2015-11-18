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
#include "Framework/Scene/SceneManager.h"

#include "Application/Game/SceneGameFactory.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneTitle::SceneTitle() {
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneTitle::~SceneTitle() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneTitle::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  }
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneTitle::_Draw(void) {
}
