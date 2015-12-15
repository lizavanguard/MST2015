//==============================================================================
//
// HudManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/ServiceLocator.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectBase;
class Root;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class HudManager {
public:
  // ctor
  HudManager();

  // dtor
  ~HudManager();

  // Update
  void Update(float elapsed_time);

  // Draw
  void Draw(void);

  // Clear
  void Clear(void);

  // Push
  void Push(ObjectBase* p_object);

  // Pop
  void Pop(ObjectBase* p_object);

private:
  Root* p_root_;
};

using HudServiceLocator = liza::generic::ServiceLocator<HudManager>;
