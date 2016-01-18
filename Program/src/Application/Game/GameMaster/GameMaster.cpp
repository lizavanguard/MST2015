//==============================================================================
//
// GameMaster
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameMaster.h"

#include "Framework/Effect/EffectManager.h"
#include "Framework/Object/Hud/HudNumber/HudNumber.h"

#include "Application/game_config.h"
#include "Application/Collision/CollisionManager.h"
#include "Application/Pin/PinManager.h"
#include "Application/Pin/StandardPins.h"
#include "Application/Pin/StandardPin.h"
#include "Application/Pin/Pin.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameMaster::GameMaster(HudNumber** pp_hud_pin_number, PinManager& pin_manager, CollisionManager& collision_manager)
    : threw_count_(0)
    , is_end_game_(false)
    , is_replay_mode_(false)
    , shoot_time_(0.0f)
    , pp_hud_pin_number_(pp_hud_pin_number)
    , collision_manager_(collision_manager)
    , pin_manager_(pin_manager) {
  for (int throw_count = 0; throw_count < kThrowingMax; ++throw_count) {
    scores_[throw_count] = 0;
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameMaster::~GameMaster() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameMaster::Update(float elapsed_time) {
  if (is_replay_mode_) {
    return;
  }

  const unsigned int num_pins = collision_manager_.GetNumKilledPinsAtCurrentLoop();
  pp_hud_pin_number_[threw_count_]->AddNumber(num_pins);
  scores_[threw_count_] += num_pins;

  if (num_pins != 0) {
    auto h = EffectManagerServiceLocator::Get()->Play2D(
      "EF_GAME_Score_Count",
      kScorePositions[threw_count_].x + 10,
      kScorePositions[threw_count_].y + 10);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 200.0f, 200.0f);
  }
}

//------------------------------------------------
// スコア計算を行う
//------------------------------------------------
void GameMaster::CalculateScore(void) {
  unsigned int num_pins = 0;
  auto& standard_pins = pin_manager_.GetStandardPins();
  for (auto pin : standard_pins) {
    const D3DXVECTOR3 rotation = pin->GetRotation();
    if (_IsFallen(rotation)) {
      ++num_pins;
    }
  }

  pp_hud_pin_number_[threw_count_]->AddNumber(num_pins);
  scores_[threw_count_] += num_pins;
  if (num_pins != 0) {
    auto h = EffectManagerServiceLocator::Get()->Play2D(
      "EF_GAME_Score_Count",
      kScorePositions[threw_count_].x + 10,
      kScorePositions[threw_count_].y + 10);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 200.0f, 200.0f);
  }
}

//------------------------------------------------
// 倒れているかのチェック
//------------------------------------------------
bool GameMaster::_IsFallen(const D3DXVECTOR3& rotation) const {
  const float kRange = 0.99f;
  return abs(rotation.y) <= kRange;
}
