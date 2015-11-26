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

#include "Framework/Object/Hud/HudNumber/HudNumber.h"

#include "Application/Collision/CollisionManager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameMaster::GameMaster(HudNumber& hud_pin_number, PinManager& pin_manager, CollisionManager& collision_manager)
    : threw_count_(0)
    , is_end_game_(false)
    , hud_pin_number_(hud_pin_number)
    , collision_manager_(collision_manager)
    , pin_manager_(pin_manager) {
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
  hud_pin_number_.AddNumber( collision_manager_.GetNumKilledPinsAtCurrentLoop());
}
