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

protected:
  // ctor
  Object();

  // dtor
  virtual ~Object();

public:

  // Create Object
  // Required: bool Initialize(anything);
  template<typename T, typename ...Args>
  static T* Create(Args... args) {
    // TODO: Type Check

    T* p = new T();
    MY_BREAK_NULL_ASSERT(p);
    if (!p) {
      return nullptr;
    }

    if (!p->Initialize(args...)) {
      MY_BREAK_ASSERTMSG(false, "èâä˙âªé∏îsÇæÇÊ");
      return nullptr;
    }

    return p;
  }

  // Destroy
  // Required: bool Uninitialize(void);
  template<typename T>
  static bool Destroy(T* p) {
    if (!p->Uninitialize()) {
      MY_BREAK_ASSERTMSG(false, "èIóπèàóùé∏îsÇæÇÊ");
      return false;
    }
    SafeDelete(p);
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
