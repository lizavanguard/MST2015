//==============================================================================
//
// factory
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <assert.h>
#include <utility>

#include <liza/generic/noncopyable.h>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
  namespace generic {

// HeaderÇéQè∆
template<typename T>
class Factory : private liza::generic::NonCopyable<Factory<T>> {
public:
  // Create object
  template<typename ...Args>
  static T* Create(Args&&... args) {
    T* p = new T(std::forward<Args>(args)...);
    assert(p != nullptr);
    return p;
  }
};

  }  // namespace generic
}  // namespace liza
