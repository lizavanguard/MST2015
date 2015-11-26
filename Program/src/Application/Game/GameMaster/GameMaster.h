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
  static const int kThrowCountMax = 2;

public:
  // ctor
  GameMaster(HudNumber& hud_pin_number, PinManager& pin_manager, CollisionManager& collision_master);

  // dtor
  ~GameMaster();

  // update
  void Update(float elapsed_time);

  // add threw count
  void GoToNextThrowing(void) { ++threw_count_; }

  // end game
  void EndGame(void) { is_end_game_ = true; }

  // get
  unsigned int GetThrowCount(void) const { return threw_count_; }
  bool IsLastThrow(void) const { return threw_count_ == kThrowCountMax - 1; }
  bool IsEndGame(void) const { return is_end_game_; }

private:
  unsigned int threw_count_;
  bool is_end_game_;

  HudNumber& hud_pin_number_;
  CollisionManager& collision_manager_;
  PinManager& pin_manager_;
};
