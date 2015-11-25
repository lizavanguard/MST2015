//==============================================================================
//
// GameStateReady
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateReady.h"
#include "GameStatePlayerInput.h"

#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"


//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 3.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateReady::GameStateReady(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  p_root_ = new Root();
  p_root_->AttachChild(Object2DFactory::Create("Game/ready", D3DXVECTOR3(200, 200, 0), D3DXVECTOR2(300, 300)));
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateReady::~GameStateReady() {
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStateReady::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    scene_game_.ChangeGameState(new GameStatePlayerInput(scene_game_));
  }

  p_root_->UpdateAll(elapsed_time);

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateReady::Draw(void) {
  p_root_->DrawAll();
}
