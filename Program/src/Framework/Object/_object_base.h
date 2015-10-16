//==============================================================================
//
// _ObjectBase
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _ObjectBase {
private:
  // alias
  using ContainerType = std::list<_ObjectBase*>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  _ObjectBase();

  // dtor
  virtual ~_ObjectBase();

  // Destroy
  static bool Destroy(_ObjectBase* p) {
    if (p) {
      delete p;
      p = nullptr;
    }
    return true;
  }

  // Attach child on list
  void AttachChild(_ObjectBase* p_child);

  // Detach child on list
  void DetachChild(_ObjectBase* p_child);

  // Update-All in list
  void UpdateAll(float elapsed_time);

  // Draw All in list
  void DrawAll(void);

private:
  // Update
  virtual void _Update(float elapsed_time) = 0;

  // Draw
  virtual void _Draw(void) = 0;

  // property
  ContainerType list_;
  bool is_all_updated_;
  bool is_all_drawed_;
  bool is_child_updated_;
  bool is_child_drawed_;
};
