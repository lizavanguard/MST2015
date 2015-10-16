//==============================================================================
//
// Object
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "_object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
class Object
  : public _ObjectBase
  , public liza::generic::NonCopyable<Object<T>> {
public:
  // Create _ObjectBase
  template<typename ...Args>
  static T* Create(Args... args) {
    T* p = new T(args...);
    MY_BREAK_NULL_ASSERT(p);
    if (!p) {
      return nullptr;
    }

    return p;
  }

};
