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
#include "Application/Pin/PinManager.h"
#include "Application/Pin/StandardPin.h"
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
      p_standard_pin->ReactCollision(pin_position - player_position);
    }
  }  // player x standard_pins

  // player x lane_pins
  {
    const D3DXVECTOR3 player_position = player_.GetPosition();
    const float player_size = player_.GetSize();

    for (auto p_lane_pin : pin_manager_.GetLanePins()) {
      if (p_lane_pin->IsCollided()) {
        continue;
      }
      const D3DXVECTOR3 pin_position = p_lane_pin->GetPosition();
      const float pin_size = p_lane_pin->GetSize();
      const bool is_intersected = IsSphereHit2(player_position.x, player_position.z, player_size, pin_position.x, pin_position.z, pin_size);
      if (!is_intersected) {
        continue;
      }
      p_lane_pin->ReactCollision(pin_position - player_position);
    }
  }

  // standard_pin x standard_pins
  {
    auto& standard_pins = pin_manager_.GetStandardPins();
    for (unsigned int i = 0; i < standard_pins.size(); ++i) {
      const D3DXVECTOR3 pin_position_a = standard_pins[i]->GetPosition();
      const float pin_size_a = standard_pins[i]->GetSize();

      for (unsigned int j = i + 1; j < standard_pins.size(); ++j) {
        const D3DXVECTOR3 pin_position_b = standard_pins[j]->GetPosition();
        const float pin_size_b = standard_pins[j]->GetSize();

        const bool is_intersected = IsSphereHit2(pin_position_a.x, pin_position_a.z, pin_size_a, pin_position_b.x, pin_position_b.z, pin_size_b);
        if (!is_intersected) {
          continue;
        }
        standard_pins[j]->ReactCollision(pin_position_b - pin_position_a);
      }
    }
  }
}
