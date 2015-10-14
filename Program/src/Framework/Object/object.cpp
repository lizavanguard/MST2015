//==============================================================================
//
// Object
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Object.h"
#include <assert.h>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Object::Object()
    : is_all_updated_(true)
    , is_all_drawed_(true)
    , is_child_updated_(true)
    , is_child_drawed_(true) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object::~Object() {
  for (auto p_child: list_) {
    delete p_child;
  }
}

//------------------------------------------------
// Attach child
//------------------------------------------------
void Object::AttachChild(Object* const p_child) {
#ifdef _DEBUG
  for (auto p_child_in_list : list_) {
    MY_BREAK_ASSERTMSG(p_child != p_child_in_list, "同じオブジェクトをアタッチしようとしています");
  }
#endif
  MY_BREAK_NULL_ASSERT(p_child);
  list_.push_back(p_child);
}

//------------------------------------------------
// Detach child
//------------------------------------------------
void Object::DetachChild(Object* const p_child) {
  MY_BREAK_NULL_ASSERT(p_child);
  for (auto p_child_in_list : list_) {
    if (p_child == p_child_in_list) {
      list_.remove(p_child);
      return;
    }
  }
}

//------------------------------------------------
// Update-All
//------------------------------------------------
void Object::UpdateAll(const float elapsed_time) {
  if (!is_all_updated_) {
    return;
  }

  _Update(elapsed_time);

  if (!is_child_updated_) {
    return;
  }
  for (auto p_chlid : list_) {
    p_chlid->UpdateAll(elapsed_time);
  }
}

//------------------------------------------------
// Draw-All
//------------------------------------------------
void Object::DrawAll(void) {
  if (!is_all_drawed_) {
    return;
  }

  _Draw();

  if (!is_child_drawed_) {
    return;
  }
  for (auto p_chlid : list_) {
    p_chlid->DrawAll();
  }
}
