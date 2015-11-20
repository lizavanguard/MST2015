//==============================================================================
//
// ServiceLocator
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <array>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
  namespace generic {

// ポインタのタイプ
template<typename T_ServiceProvider, int N>
struct ServiceLocatorArray {
  using ContainerType = std::array<T_ServiceProvider*, N>;

  // accessor
  static T_ServiceProvider* Get(unsigned int index) { return s_container_[index]; }

  // Provide a service
  static void Provide(T_ServiceProvider* p_service, unsigned int index) { s_container_[index] = p_service; }

private:
  static ContainerType s_container_;
};

template<typename T_ServiceProvider, int N>
typename ServiceLocatorArray<T_ServiceProvider, N>::ContainerType ServiceLocatorArray<T_ServiceProvider, N>::s_container_;

  }  // namespace generic
}  // namespace liza
