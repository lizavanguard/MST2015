//==============================================================================
//
// GameStateThrown
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameStateThrown.h"
#include "GameStateReady.h"

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
GameStateThrown::GameStateThrown(SceneGame& scene_game)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  p_root_ = new Root();
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateThrown::~GameStateThrown() {
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStateThrown::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    scene_game_.ChangeGameState(new GameStateReady(scene_game_));
    scene_game_.Reset();
  }

  p_root_->UpdateAll(elapsed_time);

  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateThrown::Draw(void) {
  p_root_->DrawAll();
}
