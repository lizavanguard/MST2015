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
#include "GameMaster/GameMaster.h"

#include "Framework/Object/object2d.h"
#include "Framework/Object/root.h"
#include "Framework/Object/Hud/HudNumber/HudNumber.h"
#include "Framework/Sound/sound_manager.h"
#include "Framework/Effect/EffectManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kReadyTime = 4.0f;
  const char* kThrowCountEffectName[] = {
    "EF_Game_firstThrowSign", "EF_Game_secondThrowSign"
  };
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameStateReady::GameStateReady(SceneGame& scene_game, const unsigned int throw_count)
    : GameState(scene_game)
    , p_root_(nullptr)
    , ready_time_(kReadyTime) {
  auto h = EffectManagerServiceLocator::Get()->Play2D(kThrowCountEffectName[throw_count], 640, 300);
  EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);
  //p_root_ = RootFactory::Create();
  //p_root_->AttachChild(Object2DFactory::Create("Game/ready", D3DXVECTOR3(200 + 500, 200, 0), D3DXVECTOR2(300, 300)));

  //scene_game_.Attach2D(Object2DFactory::Create(
  //  kThrowCountTexturename[throw_count],
  //  D3DXVECTOR3(100, 150, 0),
  //  D3DXVECTOR2(50, 50)));
  //scene_game_.Attach2D(p_root_);
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameStateReady::~GameStateReady() {
  //scene_game_.Detatch2D(p_root_);
  //Root::Destroy(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameStateReady::Update(const float elapsed_time) {
  if (ready_time_ <= 0.0f) {
    scene_game_.ChangeGameState(new GameStatePlayerInput(scene_game_));
  }
  ready_time_ -= elapsed_time;
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameStateReady::Draw(void) {
}
