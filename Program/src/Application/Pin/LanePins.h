//==============================================================================
//
// LanePins
// Author: Shimizu Shoji
//
// lane の 情報を何かで与える？
// ->レーンのピンを配置する必要がありそう
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
class ObjectInstancingModel;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class LanePins : public ObjectBase {
  using DataType = LanePin*;
  using ContainerType = std::deque<DataType>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  LanePins();

  // dtor
  ~LanePins();

  // Reset
  void Reset(void);

  // iterator
  Iterator begin(void) { return pins_.begin(); }
  ConstIterator begin(void) const { return pins_.begin(); }
  Iterator end(void) { return pins_.end(); }
  ConstIterator end(void) const { return pins_.end(); }

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  ContainerType pins_;
  ObjectInstancingModel* p_instancing_model_;
};

using LanePinsFactory = liza::generic::Factory<LanePins>;
