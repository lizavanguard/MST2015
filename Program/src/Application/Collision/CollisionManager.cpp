//==============================================================================
//
// CollisionManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "CollisionManager.h"

#include "Framework/Collision/collision.h"

#include "Application/Pin/LanePin.h"
#include "Application/Pin/LanePins.h"
#include "Application/Pin/Pin.h"
#include "Application/Pin/PinManager.h"
#include "Application/Pin/StandardPins.h"
#include "Application/Player/Player.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
CollisionManager::CollisionManager(Player& player, PinManager& pin_manager)
    : player_(player)
    , pin_manager_(pin_manager) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
CollisionManager::~CollisionManager() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void CollisionManager::Update(void) {
  // player x standard_pins
  {
    const D3DXVECTOR3 player_position = player_.GetPosition();
    const float player_size = player_.GetSize();

    for (auto p_standard_pin : pin_manager_.GetStandardPins()) {
      const D3DXVECTOR3 pin_position = p_standard_pin->GetPosition();
      const float pin_size = p_standard_pin->GetSize();
      const bool is_intersected = IsSphereHit2(player_position.x, player_position.z, player_size, pin_position.x, pin_position.z, pin_size);
      if (!is_intersected) {
        continue;
      }
      p_standard_pin->ReactCollision();
    }
  }  // player x standard_pins

  // player x lane_pins
  {
    const D3DXVECTOR3 player_position = player_.GetPosition();
    const float player_size = player_.GetSize();

    for (auto p_lane_pin : pin_manager_.GetLanePins()) {
      const D3DXVECTOR3 pin_position = p_lane_pin->GetPosition();
      const float pin_size = p_lane_pin->GetSize();
      const bool is_intersected = IsSphereHit2(player_position.x, player_position.z, player_size, pin_position.x, pin_position.z, pin_size);
      if (!is_intersected) {
        continue;
      }
      p_lane_pin->ReactCollision();
    }
  }
}
