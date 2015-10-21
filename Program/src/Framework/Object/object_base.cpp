//==============================================================================
//
// ObjectBase
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_base.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectBase::ObjectBase()
  : is_all_updated_(true)
  , is_all_drawed_(true)
  , is_child_updated_(true)
  , is_child_drawed_(true) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectBase::~ObjectBase() {
  for (auto p_child : list_) {
    Destroy(p_child);
  }
}

//------------------------------------------------
// Attach child
//------------------------------------------------
void ObjectBase::AttachChild(ObjectBase* const p_child) {
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
void ObjectBase::DetachChild(ObjectBase* const p_child) {
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
void ObjectBase::UpdateAll(const float elapsed_time) {
  if (!is_all_updated_) {
    return;
  }

  _Update(elapsed_time);

  if (!is_child_updated_) {
    return;
  }
  for (auto p_child : list_) {
    p_child->UpdateAll(elapsed_time);
  }
}

//------------------------------------------------
// Draw-All
//------------------------------------------------
void ObjectBase::DrawAll(void) {
  if (!is_all_drawed_) {
    return;
  }

  _Draw();

  if (!is_child_drawed_) {
    return;
  }
  for (auto p_child : list_) {
    p_child->DrawAll();
  }
}
