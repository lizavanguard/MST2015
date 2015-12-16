//==============================================================================
//
// HudManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "HudManager.h"

#include "Framework/Object/root.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
HudManager::HudManager() : p_root_(nullptr), p_root_alpha_object_(nullptr) {
  p_root_ = new Root();
  p_root_alpha_object_ = new Root();
}

//------------------------------------------------
// dtor
//------------------------------------------------
HudManager::~HudManager() {
  SafeDelete(p_root_alpha_object_);
  SafeDelete(p_root_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void HudManager::Update(const float elapsed_time) {
  p_root_->UpdateAll(elapsed_time);
  p_root_alpha_object_->UpdateAll(elapsed_time);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void HudManager::Draw(void) {
  p_root_->DrawAll();
}

void HudManager::DrawAlphaHud(void) {
  p_root_alpha_object_->DrawAll();
}
//------------------------------------------------
// Clear
//------------------------------------------------
void HudManager::Clear(void) {
  p_root_->DestroyChilds();
  p_root_alpha_object_->DestroyChilds();
}

//------------------------------------------------
// Push
//------------------------------------------------
void HudManager::Push(ObjectBase* p_object) {
  p_root_->AttachChild(p_object);
}

void HudManager::PushAlphaHud(ObjectBase* p_object) {
  p_root_alpha_object_->AttachChild(p_object);
}

//------------------------------------------------
// Pop
//------------------------------------------------
void HudManager::Pop(ObjectBase* p_object) {
  p_root_->DetachChild(p_object);
}

void HudManager::PopAlphaHud(ObjectBase* p_object) {
  p_root_alpha_object_->DetachChild(p_object);
}
