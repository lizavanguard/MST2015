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
#include "Framework/Object/object_cube_mapping.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class PlayerBall : public ObjectCubeMapping {
public:
  // ctor
  PlayerBall(CubeTextureForEnvironmentMapping::ObjectDrawer* p_object_drawer);

  // dtor
  virtual ~PlayerBall();

  // Reset
  void Reset(void);

  // set
  void Shoot(float rotation);

  // Change
  void ChangeDrawingOuterFace(bool is_drawn_outer_face);

  // set
  void SetRotationPower(float rotation_power) { rotation_power_ = rotation_power; }
  void AddRotationPower(float rotation_power) { rotation_power_ += rotation_power; }
  void ZRotationPower(float z_rotation_power) { z_rotation_power = z_rotation_power; }

private:
  virtual void _Update(float elapsed_time) override;
  //virtual void _Draw(void) override;

  float rotation_power_;
  D3DXVECTOR3 rotation_axis_;
  float z_rotation_power_;
};
