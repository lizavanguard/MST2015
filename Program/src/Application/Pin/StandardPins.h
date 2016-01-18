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
class StandardPin;
class SceneGame;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class StandardPins : public ObjectBase {
  static const int kNumPins = 10;
  using DataType = StandardPin*;
  using ContainerType = std::array<DataType, kNumPins>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  StandardPins(const D3DXVECTOR3& center_position, const D3DXVECTOR3& rotation, SceneGame* p_scene_game = nullptr);

  // dtor
  ~StandardPins();

  // Reset
  void Reset(void);

  // iterator
  Iterator begin(void) { return pins_.begin(); }
  ConstIterator begin(void) const { return pins_.begin(); }
  Iterator end(void) { return pins_.end(); }
  ConstIterator end(void) const { return pins_.end(); }
  ContainerType::size_type size(void) const { return pins_.size(); }

  // operator
  DataType operator[](unsigned int index) { return pins_[index]; }
  const DataType operator[](unsigned int index) const { return pins_[index]; }

private:
  DEFINITION_DEFAULT_UPDATE_AND_DRAW
  ContainerType pins_;
};

using StandardPinsFactory = liza::generic::Factory<StandardPins>;
