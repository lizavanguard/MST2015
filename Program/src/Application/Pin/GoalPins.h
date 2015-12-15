//==============================================================================
//
// GoalPins
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Collision/collision_object.h"
#include "Framework/Object/object_base.h"

#include "liza/generic/factory.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GoalPin;
class ObjectInstancingModel;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GoalPins : public ObjectBase, public CollisionObject {
  static const int kNumPins = 100;
  using DataType = GoalPin*;
  using ContainerType = std::array<DataType, kNumPins>;
  using Iterator = ContainerType::iterator;
  using ConstIterator = ContainerType::const_iterator;

public:
  // ctor
  GoalPins(const D3DXVECTOR3& center_position, float r);

  // dtor
  ~GoalPins();

  // Reset
  void Reset(void);

  // React collision
  virtual void ReactCollision(const D3DXVECTOR3& power) override;

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
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  ContainerType pins_;
  ObjectInstancingModel* p_instancing_model_;
};

using GoalPinsFactory = liza::generic::Factory<GoalPins>;
