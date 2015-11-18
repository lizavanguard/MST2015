//==============================================================================
//
// Controller
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class InputKeyboard;
class Player;
class CWiiController;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Controller {
public:
  // ctor
  Controller(Player& player);

  // dtor
  ~Controller();

  // Update
  void Update(void);

  // Change current WiiControllerID
  void ChangeCurrentWiiControllerID(unsigned int wii_controller_id);

private:
  bool _IsMovedToLeft(void);
  bool _IsMovedToRight(void);
  bool _IsSetUp(void);
  bool _IsShot(void);
  float _GetControllerRotation(void);

  // property
  Player& player_;
  const InputKeyboard& keyboard_;
  CWiiController& wii_controller_;

  float old_rotation_;
};
