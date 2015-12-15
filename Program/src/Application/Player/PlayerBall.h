//==============================================================================
//
// PlayerBall
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_model.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class PlayerBall : public ObjectModel {
public:
  // ctor
  PlayerBall();

  // dtor
  virtual ~PlayerBall();

  // Reset
  void Reset(void);

  // set
  void Shoot(float rotation);

  // set
  void SetRotationPower(float rotation_power) { rotation_power_ = rotation_power; }
  void AddRotationPower(float rotation_power) { rotation_power_ += rotation_power; }

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  float rotation_power_;
  D3DXVECTOR3 rotation_axis_;
};
