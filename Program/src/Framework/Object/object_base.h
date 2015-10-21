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

protected:
  // property
  bool is_all_updated_;
  bool is_all_drawed_;
  bool is_child_updated_;
  bool is_child_drawed_;

private:
  // Update
  virtual void _Update(float elapsed_time) = 0;

  // Draw
  virtual void _Draw(void) = 0;

  // property
  ContainerType list_;
};
