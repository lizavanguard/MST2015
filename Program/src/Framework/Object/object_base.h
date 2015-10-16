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
#include "object.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
class ObjectBase
    : public Object
    , public liza::generic::NonCopyable<ObjectBase<T>> {
public:
  // Create Object
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
