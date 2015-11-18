//==============================================================================
//
// Controller
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Controller.h"

#include "Application/Player/Player.h"
#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Controller::Controller(Player& player)
    : player_(player)
    , keyboard_(GameManager::Instance().GetInputManager().GetPrimaryKeyboard())
    , wii_controller_(WiiControllerManager::Instance().GetWiiController(0)) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Controller::~Controller() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Controller::Update(void) {
#ifdef _DEBUG
  static float throwed_rotation = 0;
#endif
  if (_IsMovedToLeft()) {
    player_.MoveLeft();
  }
  if (_IsMovedToRight()) {
    player_.MoveRight();
  }

  if (_IsSetUp()) {
    old_rotation_ = _GetControllerRotation();
  }
  else if (_IsShot()) {
    float rotation = _GetControllerRotation();
    player_.Shoot(rotation - old_rotation_);

#ifdef _DEBUG
    throwed_rotation = rotation - old_rotation_;
#endif
  }

#ifdef _DEBUG
  DebugProc::Print("ç≈èIìäÇ∞ÇÁÇÍÇΩäpìx[%.4f]\n", throwed_rotation);
#endif
}

//------------------------------------------------
// Change current WiiControllerID
//------------------------------------------------
void Controller::ChangeCurrentWiiControllerID(const unsigned int wii_controller_id) {
  wii_controller_ = WiiControllerManager::Instance().GetWiiController(wii_controller_id);
}

//------------------------------------------------
// get
//------------------------------------------------
bool Controller::_IsMovedToLeft(void) {
  return keyboard_.IsPress(DIK_A) || wii_controller_.getPress(WC_LEFT);
}

bool Controller::_IsMovedToRight(void) {
  return keyboard_.IsPress(DIK_D) || wii_controller_.getPress(WC_RIGHT);
}

bool Controller::_IsSetUp(void) {
  return keyboard_.IsTrigger(DIK_LCONTROL) || wii_controller_.getTrigger(WC_A);
}

bool Controller::_IsShot(void) {
  return keyboard_.IsRelease(DIK_LCONTROL) || wii_controller_.getRelease(WC_A);
}

float Controller::_GetControllerRotation(void) {
  return wii_controller_.getAccelerationX();
}
