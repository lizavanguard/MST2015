//==============================================================================
//
// ObjectBase
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <liza/generic/noncopyable.h>

#include "Framework/Camera/camera_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectBase : public liza::generic::NonCopyable<ObjectBase> {
private:
  // alias
  using ContainerType = std::list<ObjectBase*>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;
  using CameraHandle = _CameraManager::CameraHandle;

protected:
  // ctor
  ObjectBase();

  // dtor
  virtual ~ObjectBase();

public:
  // Destroy
  static bool Destroy(ObjectBase* p) {
    if (p) {
      delete p;
      p = nullptr;
    }
    return true;
  }

  // Attach child on list
  void AttachChild(ObjectBase* p_child);

  // Detach child on list
  void DetachChild(ObjectBase* p_child);

  // Update-All in list
  void UpdateAll(float elapsed_time);

  // Draw All in list
  void DrawAll(void);

  // get
  const D3DXMATRIX& GetWorldMatrix(void) const { return world_matrix_; }
  const D3DXVECTOR3& GetPosition(void) const { return position_; }
  const D3DXVECTOR3& GetRotation(void) const { return rotation_; }
  const D3DXVECTOR3& GetScale(void) const { return scale_; }
  const D3DXVECTOR3& GetVelocity(void) const { return velocity_; }

  // set
  void SetPosition(const D3DXVECTOR3& position) { position_ = position; }
  void SetRotation(const D3DXVECTOR3& rotation) { rotation_ = rotation; }
  void SetScale(const D3DXVECTOR3& scale) { scale_ = scale; }
  void SetRotationMatrix(const D3DXMATRIX& rotation_matrix) { rotation_matrix_ = rotation_matrix; }
  void SetCameraHandle(CameraHandle camera_handle) { camera_handle_ = camera_handle; }
  void OnAllDrawed(void) { is_all_drawed_ = true; }
  void OffAllDrawed(void) { is_all_drawed_ = false; }


protected:
  // 直下の子供を返すよ
  ObjectBase& GetChild(unsigned int index);

  // 通常、子の呼び出しは自動で行われます
  // この関数は、子の呼び出しを手動で行う必要がある時のみ使用してください
  // 例えば、子呼び出しの前後に処理を挟みたい時などに効果的です
  void _UpdateChildAll(float elapsed_time);
  void _DrawChildAll(void);

  // property
  D3DXVECTOR3 position_;
  D3DXVECTOR3 rotation_;
  D3DXVECTOR3 scale_;
  D3DXVECTOR3 velocity_;

  D3DXMATRIX world_matrix_;  // ツリー構造の今まで全てのワールド行列が反映されたもの
  D3DXMATRIX own_world_matrix_;  // 自分自身のワールド行列

  D3DXMATRIX rotation_matrix_;

  ObjectBase* p_parent_;
  CameraHandle camera_handle_;

  bool is_all_updated_;
  bool is_all_drawed_;
  bool is_child_auto_updated_;
  bool is_child_auto_drawed_;
  bool is_calculated_parent_matrix_;

private:
  // Update
  virtual void _Update(float elapsed_time) = 0;

  // Draw
  virtual void _Draw(void) = 0;

  // calculate world-matrix
  void _CalculateWorldMatrix(void);

  // property
  ContainerType list_;
};

#define DEFINITION_DEFAULT_UPDATE virtual void _Update(float elapsed_time) override {}
#define DEFINITION_DEFAULT_DRAW virtual void _Draw(void) override {}
#define DEFINITION_DEFAULT_UPDATE_AND_DRAW DEFINITION_DEFAULT_UPDATE DEFINITION_DEFAULT_DRAW
