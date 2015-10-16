//==============================================================================
//
// Object
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object {
private:
  // alias
  typedef std::list<Object*> ContainerType;
  typedef ContainerType::iterator Iterator;
  typedef ContainerType::const_iterator ConstIterator;

public:
  // ctor
  Object();

  // dtor
  virtual ~Object();

  // Destroy
  static bool Destroy(Object* p) {
    if (p) {
      delete p;
      p = nullptr;
    }
    return true;
  }

  // Attach child on list
  void AttachChild(Object* p_child);

  // Detach child on list
  void DetachChild(Object* p_child);

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
