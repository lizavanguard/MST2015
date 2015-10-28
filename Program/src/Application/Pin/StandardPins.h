//==============================================================================
//
// StandardPins
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_base.h"

#include "liza/generic/factory.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Pin;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class StandardPins : public ObjectBase {
  static const int kNumPins = 10;
  using ContainerType = std::array<Pin*, kNumPins>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  StandardPins(const D3DXVECTOR3& center_position, const D3DXVECTOR3& rotation);

  // dtor
  ~StandardPins();

  // iterator
  Iterator begin(void) { return pins_.begin(); }
  ConstIterator begin(void) const { return pins_.begin(); }
  Iterator end(void) { return pins_.end(); }
  ConstIterator end(void) const { return pins_.end(); }

private:
  DEFINITION_DEFAULT_UPDATE_AND_DRAW
  ContainerType pins_;
};

using StandardPinsFactory = liza::generic::Factory<StandardPins>;
