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
    container_[controller_count] = new CWiiController();
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
    container_[controller_count]->update();
  }
}
