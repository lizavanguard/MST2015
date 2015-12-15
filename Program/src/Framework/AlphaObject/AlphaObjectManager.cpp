//==============================================================================
//
// AlphaObjectManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "AlphaObjectManager.h"

#include "Framework/Object/root.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
AlphaObjectManager::AlphaObjectManager() {
  p_root_ = new Root();
}

//------------------------------------------------
// dtor
//------------------------------------------------
AlphaObjectManager::~AlphaObjectManager() {
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void AlphaObjectManager::Update(const float elapsed_time) {
  p_root_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void AlphaObjectManager::Draw(void) {
  p_root_->DrawAll();
}

//------------------------------------------------
// Clear
//------------------------------------------------
void AlphaObjectManager::Clear(void) {
  p_root_->DestroyChilds();
}

//------------------------------------------------
// Push
//------------------------------------------------
void AlphaObjectManager::Push(ObjectBase* p_object) {
  p_root_->AttachChild(p_object);
}
