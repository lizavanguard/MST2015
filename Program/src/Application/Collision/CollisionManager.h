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

private:
  Player& player_;
  PinManager& pin_manager_;
};
