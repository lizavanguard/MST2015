//==============================================================================
//
// LanePins
// Author: Shimizu Shoji
//
// lane ÇÃ èÓïÒÇâΩÇ©Ç≈ó^Ç¶ÇÈÅH
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_base.h"

#include "liza/generic/factory.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class LanePin;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class LanePins : public ObjectBase {
  using ContainerType = std::deque<LanePin*>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  LanePins();

  // dtor
  ~LanePins();

  // iterator
  Iterator begin(void) { return pins_.begin(); }
  ConstIterator begin(void) const { return pins_.begin(); }
  Iterator end(void) { return pins_.end(); }
  ConstIterator end(void) const { return pins_.end(); }

private:
  DEFINITION_DEFAULT_UPDATE_AND_DRAW
  ContainerType pins_;
};

using LanePinsFactory = liza::generic::Factory<LanePins>;
