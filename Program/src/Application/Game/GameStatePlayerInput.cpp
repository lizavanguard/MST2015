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
#include "GameStateThrown.h"

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
GameStatePlayerInput::GameStatePlayerInput(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr) {
  p_root_ = new Root();
  p_root_->AttachChild(Object2DFactory::Create("Game/please_throw", D3DXVECTOR3(200 + 500, 200, 0), D3DXVECTOR2(300, 300)));
  p_controller_ = new Controller(scene_game.GetPlayer(), scene_game_.GetPinManager());
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStatePlayerInput::~GameStatePlayerInput() {
  SafeDelete(p_controller_);
  Root::Destroy(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStatePlayerInput::Update(const float elapsed_time) {
  if (p_controller_->Update()) {
    scene_game_.ChangeGameState(new GameStateThrown(scene_game_));
  }

  p_root_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStatePlayerInput::Draw(void) {
  p_root_->DrawAll();
}
