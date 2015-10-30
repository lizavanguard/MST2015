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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectBase : public liza::generic::NonCopyable<ObjectBase> {
private:
  // alias
  using ContainerType = std::list<ObjectBase*>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

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

protected:
  // property
  D3DXVECTOR3 position_;
  D3DXVECTOR3 rotation_;
  D3DXVECTOR3 scale_;
  D3DXVECTOR3 velocity_;

  D3DXMATRIX world_matrix_;  // ツリー構造の今まで全てのワールド行列が反映されたもの
  D3DXMATRIX own_world_matrix_;  // 自分自身のワールド行列

  ObjectBase* p_parent_;

  bool is_all_updated_;
  bool is_all_drawed_;
  bool is_child_updated_;
  bool is_child_drawed_;
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
