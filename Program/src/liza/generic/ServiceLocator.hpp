//==============================================================================
//
// ServiceLocator
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
  namespace generic {

// ポインタのタイプ
template<typename T_ServiceProvider>
struct ServiceLocator {
  // accessor
  static T_ServiceProvider* Get(void) { return s_p_serivce_; }

  // Provide a service
  static void Provide(T_ServiceProvider* p_service) { s_p_serivce_ = p_service; }

private:
  static T_ServiceProvider* s_p_serivce_;
};

template<typename T_ServiceProvider>
T_ServiceProvider* ServiceLocator<T_ServiceProvider>::s_p_serivce_ = nullptr;


// 参照のタイプ
template<typename T_ServiceProvider, typename T_NullServiceProvider>
struct ServiceLocatorRefferenceVersion {
  // accessor
  static T_ServiceProvider& Get(void) { return *s_p_service_; }

  // Provide a service
  static void Provide(T_ServiceProvider* p_service) {
    if (p_service) {
      s_p_service_ = p_service;
    }
    else {
      s_p_service_ = &s_null_service_;
    }
  }

private:
  static T_NullServiceProvider s_null_service_;
  static T_ServiceProvider* s_p_service_;
};

template<typename T_ServiceProvider, typename T_NullServiceProvider>
T_NullServiceProvider ServiceLocatorRefferenceVersion<T_ServiceProvider, T_NullServiceProvider>::s_null_service_;

template<typename T_ServiceProvider, typename T_NullServiceProvider>
T_ServiceProvider* ServiceLocatorRefferenceVersion<T_ServiceProvider, T_NullServiceProvider>::s_p_service_ = &s_null_service_;

  }  // namespace generic
}  // namespace liza
