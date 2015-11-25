//==============================================================================
//
// GameStatePlayerInput
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStatePlayerInput.h"

#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"

#include "Application/Controller/Controller.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 5.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStatePlayerInput::GameStatePlayerInput()
    : p_root_(nullptr) {
  p_root_ = new Root();
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStatePlayerInput::~GameStatePlayerInput() {
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStatePlayerInput::Update(const float elapsed_time, SceneGame::GameState* p_next_state) {
  p_root_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStatePlayerInput::Draw(void) {
  p_root_->DrawAll();
}
