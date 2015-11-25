//==============================================================================
//
// GameMaster
// Author: Shimizu Shoji
//
// STATE:
//  READY
//  PLAYER_INPUT
//  WATCH
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CollisionManager;
class HudNumber;
class PinManager;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameMaster {

public:
  // ctor
  GameMaster(HudNumber& hud_pin_number, PinManager& pin_manager, CollisionManager& collision_master);

  // dtor
  ~GameMaster();

  // update
  void Update(float elapsed_time);

private:
  unsigned int threw_count_;
  HudNumber& hud_pin_number_;

  CollisionManager& collision_manager_;
  PinManager& pin_manager_;
};
