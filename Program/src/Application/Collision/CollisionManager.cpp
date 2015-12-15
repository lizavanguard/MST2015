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

#include "Application/Pin/GoalPin.h"
#include "Application/Pin/GoalPins.h"
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
    , pin_manager_(pin_manager)
    , num_killed_pins_at_current_loop_(0) {
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
  num_killed_pins_at_current_loop_ = 0;

  // player x lane_pins
  {
    const D3DXVECTOR3& player_position = player_.GetPosition();
    const float player_size = player_.GetSize();

    for (auto p_lane_pin : pin_manager_.GetLanePins()) {
      if (p_lane_pin->IsCollided()) {
        continue;
      }
      const D3DXVECTOR3& pin_position = p_lane_pin->GetPosition();
      const float pin_size = p_lane_pin->GetSize();
      const bool is_intersected = IsSphereHit2(player_position.x, player_position.z, player_size, pin_position.x, pin_position.z, pin_size);
      if (!is_intersected) {
        continue;
      }
      p_lane_pin->ReactCollision(pin_position - player_position);
      ++num_killed_pins_at_current_loop_;
    }
  }

  {  // player x goal_pins
    auto& goal_pins = pin_manager_.GetGoalPins();
    if (goal_pins.IsCollided()) {
      return;
    }
    const D3DXVECTOR3& player_position = player_.GetPosition();
    const float player_size = player_.GetSize();

    const D3DXVECTOR3& pins_position = goal_pins.GetPosition();
    const float pins_size = goal_pins.GetSize();

    const float kCollisionSizeY = 200.0f;
    const bool is_y_close = (player_position.y - pins_position.y) <= kCollisionSizeY;
    if (!is_y_close) {
      return;
    }

    const bool is_intersected = IsSphereHit2(player_position.x, player_position.z, player_size, pins_position.x, pins_position.z, pins_size);
    if (is_intersected) {
      goal_pins.ReactCollision(player_position);
    }
  }
}
