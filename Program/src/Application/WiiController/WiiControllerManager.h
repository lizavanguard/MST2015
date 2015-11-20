//==============================================================================
//
// WiiControllerManager
// Author: Shimizu Shoji
//
// ì¡Ç…ä«óùÇ∑ÇÈÇÌÇØÇ≈ÇÕÇ»Ç¢(???
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/SingletonHolder.hpp"
#include "liza/generic/ServiceLocatorArray.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CWiiController;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _WiiControllerManager {
public:
  static const int kNumControllers = 2;
  using ContainerType = std::array<CWiiController*, kNumControllers>;

public:
  // ctor
  _WiiControllerManager();

  // dtor
  ~_WiiControllerManager();

  // Update
  void Update(void);

  // getp
  CWiiController* GetWiiController(unsigned int index) { return container_[index]; }
  const CWiiController* GetWiiController(unsigned int index) const { return container_[index]; }

private:
  ContainerType container_;
};

struct Locator {
  static CWiiController* GetWiiController(unsigned int index) {
    return s_container_[index];
  }

  static void Provide(CWiiController* p_controller, unsigned int index) {
    s_container_[index] = p_controller;
  }

private:
  using ContainerType = std::array<CWiiController*, 2>;
  static ContainerType s_container_;
};

using WiiControllerManager = liza::generic::SingletonHolder<_WiiControllerManager>;

using WiiControllerServiceLocator = liza::generic::ServiceLocatorArray<CWiiController, _WiiControllerManager::kNumControllers>;
