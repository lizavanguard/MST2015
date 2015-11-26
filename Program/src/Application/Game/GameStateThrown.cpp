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
#include "GameMaster/GameMaster.h"

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
    auto& game_master = scene_game_.GetGameMaster();
    if (game_master.IsLastThrow()) {
      game_master.EndGame();
      return;
    }
    game_master.GoToNextThrowing();
    scene_game_.ChangeGameState(new GameStateReady(scene_game_, game_master.GetThrowCount()));
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
