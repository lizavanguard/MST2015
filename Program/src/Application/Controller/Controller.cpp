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
#include "Application/Pin/PinManager.h"
#include "Application/WiiController/CWiiController.h"
#include "Application/WiiController/WiiControllerManager.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Controller::Controller(Player& player_, PinManager& pin_manager)
    : keyboard_(GameManager::Instance().GetInputManager().GetPrimaryKeyboard())
    , p_wii_controller_(WiiControllerManager::Instance().GetWiiController(0))
    , player_(player_)
    , pin_manager_(pin_manager)
    , is_active_(true)
    , is_set_up_(false)
#ifdef _DEBUG
    , debug_rotation_(0.0f)
    , thrown_rotation_(0.0f)
#endif
{
}

//------------------------------------------------
// dtor
//------------------------------------------------
Controller::~Controller() {
}

//------------------------------------------------
// Update
//------------------------------------------------
bool Controller::Update(void) {
  if (!is_active_) {
    return false;
  }

  if (_IsMovedToLeft()) {
    player_.MoveLeft();
  }
  if (_IsMovedToRight()) {
    player_.MoveRight();
  }

  if (_IsSetUp() && !is_set_up_) {
    old_rotation_ = _GetControllerRotation();
    is_set_up_ = true;
  }
  else if (is_set_up_ && _IsShot() ) {
    const float rotation = _CalcRotation();
    player_.Shoot(rotation);

#ifdef _DEBUG
    thrown_rotation_ = rotation;
#endif

    is_set_up_ = false;
    return true;
  }

#ifdef _DEBUG
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kDebugRotationSpeed = 0.01f;
  if (keyboard.IsPress(DIK_1)) {
    debug_rotation_ -= kDebugRotationSpeed;
  }
  if (keyboard.IsPress(DIK_2)) {
    debug_rotation_ += kDebugRotationSpeed;
  }

  if (_IsMoveToForward()) {
    player_.MoveForward();
  }
  if (_IsMoveToBackward()) {
    player_.MoveBackward();
  }
  if (_IsMoveToUp()) {
    player_.MoveUp();
  }
  if (_IsMoveToDown()) {
    player_.MoveDown();
  }

  DebugProc::Print("“Š‚°‚½Žž‚Ì‰ñ“]—Ê[%.4f]\n", thrown_rotation_);
  DebugProc::Print("ƒfƒoƒbƒOŽž‚Ì‰ñ“]—Ê[%.4f]\n", debug_rotation_);

  if (_IsResetted()) {
    player_.Reset();
    pin_manager_.Reset();
  }
#endif
  return false;
}

//------------------------------------------------
// Change current WiiControllerID
//------------------------------------------------
void Controller::ChangeCurrentWiiControllerID(const unsigned int wii_controller_id) {
  p_wii_controller_ = WiiControllerServiceLocator::Get(wii_controller_id);;
}

//------------------------------------------------
// get
//------------------------------------------------
bool Controller::_IsMovedToLeft(void) {
  const bool is_key_moved = keyboard_.IsPress(DIK_A);
  const bool is_wii_moved = p_wii_controller_ ? p_wii_controller_->getPress(WC_LEFT) : false;
  return  is_key_moved || is_wii_moved;
}

bool Controller::_IsMovedToRight(void) {
  const bool is_key_moved = keyboard_.IsPress(DIK_D);
  const bool is_wii_moved = p_wii_controller_ ? p_wii_controller_->getPress(WC_RIGHT) : false;
  return is_key_moved || is_wii_moved;
}

bool Controller::_IsSetUp(void) {
  const bool is_key_moved = keyboard_.IsTrigger(DIK_LCONTROL);
  const bool is_wii_moved = p_wii_controller_ ? p_wii_controller_->getTrigger(WC_A) : false;
  return is_key_moved || is_wii_moved;
}

bool Controller::_IsShot(void) {
  const bool is_key_moved = keyboard_.IsRelease(DIK_LCONTROL);
  const bool is_wii_moved = p_wii_controller_ ? p_wii_controller_->getRelease(WC_A) : false;
  return is_key_moved || is_wii_moved;
}

float Controller::_GetControllerRotation(void) {
  return p_wii_controller_ ? p_wii_controller_->getAccelerationX() : 0.0f;
}

float Controller::_CalcRotation(void) {
  float temp = 0.0f;
#ifdef _DEBUG
  temp = debug_rotation_;
#endif

  const float rotation = p_wii_controller_ ? _GetControllerRotation() : temp;
  return rotation - old_rotation_;
}

#ifdef _DEBUG
bool Controller::_IsResetted(void) {
  return keyboard_.IsTrigger(DIK_SPACE) || (p_wii_controller_ ? p_wii_controller_->getTrigger(WC_B) : false);
}

bool Controller::_IsMoveToForward(void) {
  return keyboard_.IsPress(DIK_W);
}

bool Controller::_IsMoveToBackward(void) {
  return keyboard_.IsPress(DIK_S);
}

bool Controller::_IsMoveToUp(void) {
  return keyboard_.IsPress(DIK_I);
}

bool Controller::_IsMoveToDown(void) {
  return keyboard_.IsPress(DIK_K);
}
#endif
