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
class CWiiController;
class InputKeyboard;
class Player;
class PinManager;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Controller {
public:
  // ctor
  Controller(Player& player, PinManager& pin_manager);

  // dtor
  ~Controller();

  // Update
  bool Update(void);

  // Change current WiiControllerID
  void ChangeCurrentWiiControllerID(unsigned int wii_controller_id);

  // active
  void PowerOn(void) { is_active_ = true; }
  void PowerOff(void) { is_active_ = false; }

private:
  bool _IsMovedToLeft(void);
  bool _IsMovedToRight(void);
  bool _IsSetUp(void);
  bool _IsShot(void);
  float _GetControllerRotation(void);
  float _CalcRotation(void);

  // property
  const InputKeyboard& keyboard_;
  CWiiController* p_wii_controller_;
  Player& player_;
  PinManager& pin_manager_;

  float old_rotation_;
  bool is_active_;
  bool is_set_up_;

#ifdef _DEBUG
  float debug_rotation_;
  float thrown_rotation_;
  bool _IsResetted(void);
#endif
};
