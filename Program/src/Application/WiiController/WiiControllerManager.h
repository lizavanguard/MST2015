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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CWiiController;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _WiiControllerManager {
  static const int kNumControllers = 2;
  using ContainerType = std::array<CWiiController*, kNumControllers>;

public:
  // ctor
  _WiiControllerManager();

  // dtor
  ~_WiiControllerManager();

  // Update
  void Update(void);

  // get
  CWiiController& GetWiiController(unsigned int index) { return *container_[index]; }

private:
  ContainerType container_;
};

using WiiControllerManager = liza::generic::SingletonHolder<_WiiControllerManager>;
