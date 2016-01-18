//==============================================================================
//
// CollisionManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Player;
class PinManager;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CollisionManager {
public:
  // ctor
  CollisionManager(Player& player, PinManager& pin_manager);

  // dtor
  ~CollisionManager();

  // Update
  void Update(void);

  // get
  unsigned int GetNumKilledPinsAtCurrentLoop(void) const { return num_killed_pins_at_current_loop_; }

private:
  // _function
  void PlayerXBiggestPin(void);
  void PlayerXGoalPins(void);
  void PlayerXLanePins(void);
  void PlayerXStandardPins(void);

  Player& player_;
  PinManager& pin_manager_;
  unsigned int num_killed_pins_at_current_loop_;
};
