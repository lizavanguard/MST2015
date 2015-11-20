//==============================================================================
//
// SceneGame
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneGame.h"

#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Scene/SceneManager.h"

#include "Application/Title/SceneTitleFactory.h"

// HACK:
#include "Application/Test/Test.h"
Test* g_p_test = nullptr;


#include "liza/generic/ServiceLocator.hpp"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
    :p_controller_(nullptr) {
  g_p_test = new Test();
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  delete g_p_test;
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneGame::_Update(SceneManager* p_scene_manager, const float elapsed_time) {
  const auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(DIK_RETURN)) {
    p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
  }

  g_p_test->Update();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::_Draw(void) {
  g_p_test->Draw();
}
