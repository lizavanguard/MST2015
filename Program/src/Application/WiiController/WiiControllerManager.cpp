//==============================================================================
//
// WiiControllerManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "WiiControllerManager.h"

#include "CWiiController.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_WiiControllerManager::_WiiControllerManager() {
  for (unsigned int controller_count = 0; controller_count < kNumControllers; ++controller_count) {
    CWiiController* p_controller = new CWiiController();
    if (p_controller->getConnectFlag()) {
      p_controller->update();
    }
    else {
      SafeDelete(p_controller);
    }
    container_[controller_count] = p_controller;
  }

  // provide to locator
  for (unsigned int controller_count = 0; controller_count < kNumControllers; ++controller_count) {
    WiiControllerServiceLocator::Provide(container_[controller_count], controller_count);
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
_WiiControllerManager::~_WiiControllerManager() {
  for (unsigned int controller_count = 0; controller_count < kNumControllers; ++controller_count) {
    SafeDelete(container_[controller_count]);
  }
}

//------------------------------------------------
// Update
//------------------------------------------------
void _WiiControllerManager::Update(void) {
  for (unsigned int controller_count = 0; controller_count < kNumControllers; ++controller_count) {
    if (container_[controller_count]) {
      container_[controller_count]->update();
    }
  }
}
