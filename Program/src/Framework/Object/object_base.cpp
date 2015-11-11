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
  : position_(0.0f, 0.0f, 0.0f)
  , rotation_(0.0f, 0.0f, 0.0f)
  , scale_(1.0f, 1.0f, 1.0f)
  , velocity_(0.0f, 0.0f, 0.0f)
  , p_parent_(nullptr)
  , camera_handle_(0)
  , is_all_updated_(true)
  , is_all_drawed_(true)
  , is_child_auto_updated_(true)
  , is_child_auto_drawed_(true)
  , is_calculated_parent_matrix_(true) {
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
  p_child->p_parent_ = this;
}

//------------------------------------------------
// Detach child
//------------------------------------------------
void ObjectBase::DetachChild(ObjectBase* const p_child) {
  MY_BREAK_NULL_ASSERT(p_child);
  for (auto p_child_in_list : list_) {
    if (p_child == p_child_in_list) {
      list_.remove(p_child);
      p_child->p_parent_ = nullptr;
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

  _CalculateWorldMatrix();

  _Update(elapsed_time);
  if (is_child_auto_updated_) {
    _UpdateChildAll(elapsed_time);
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
  if (is_child_auto_drawed_) {
    _DrawChildAll();
  }
}

//------------------------------------------------
// 通常、子の呼び出しは自動で行われます
// この関数は、子の呼び出しを手動で行う必要がある時のみ使用してください
// 例えば、子呼び出しの前後に処理を挟みたい時などに効果的です
//------------------------------------------------
void ObjectBase::_UpdateChildAll(const float elapsed_time) {
  for (auto p_child : list_) {
    p_child->UpdateAll(elapsed_time);
  }
}

void ObjectBase::_DrawChildAll(void) {
  for (auto p_child : list_) {
    p_child->DrawAll();
  }
}

//------------------------------------------------
// calculate world-matrix
//------------------------------------------------
void ObjectBase::_CalculateWorldMatrix(void) {
  D3DXMATRIX translation_matrix;
  D3DXMatrixTranslation(&translation_matrix, position_.x, position_.y, position_.z);
  D3DXMATRIX rotation_matrix;
  D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation_.y, rotation_.x, rotation_.z);
  D3DXMATRIX scale_matrix;
  D3DXMatrixScaling(&scale_matrix, scale_.x, scale_.y, scale_.z);
  own_world_matrix_ = scale_matrix * rotation_matrix * translation_matrix;

  if (p_parent_ && is_calculated_parent_matrix_) {
    world_matrix_ = p_parent_->world_matrix_ * own_world_matrix_;
  }
  else {
    world_matrix_ = own_world_matrix_;
  }
}
