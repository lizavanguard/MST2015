//==============================================================================
//
// AlphaObjectManager
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
class AlphaObjectManager {
public:
  // ctor
  AlphaObjectManager();

  // dtor
  ~AlphaObjectManager();

  // Update
  void Update(float elapsed_time);

  // Draw
  void Draw(void);

  // Clear
  void Clear(void);

  // Attach
  void Push(ObjectBase* p_object);

private:
  Root* p_root_;
};

using AlphaObjectServiceLocator = liza::generic::ServiceLocator<AlphaObjectManager>;
