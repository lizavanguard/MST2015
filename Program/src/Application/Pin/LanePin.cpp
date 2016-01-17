//==============================================================================
//
// LanePin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "LanePin.h"
#include "PinConfig.h"

#include "Framework/Effect/EffectManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kBoostEffectName = "EF_Game_floatingPinEX";
  const float kEffectScale = 5.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
LanePin::LanePin(const D3DXVECTOR3& position, const float theta, SceneGame* p_scene_game)
      : Pin(position, p_scene_game), base_position_(position), rotation_speed_(0.0f), theta_(theta), initial_theta_(theta){
  handle_ = EffectManagerServiceLocator::Get()->Play3D(kBoostEffectName, position_.x, position_.y - pin::lane_pin::kHalfSizeY, position_.z);
  EffectManagerServiceLocator::Get()->SetScale(handle_, kEffectScale, kEffectScale, kEffectScale);
  sum_time_ = 0;
}

//------------------------------------------------
// dtor
//------------------------------------------------
LanePin::~LanePin() {
  EffectManagerServiceLocator::Get()->Stop3D(handle_);
}

//------------------------------------------------
// React collision
//------------------------------------------------
void LanePin::ReactCollision(const D3DXVECTOR3& power) {
  EffectManagerServiceLocator::Get()->Stop3D(handle_);

  D3DXVECTOR3 direction;
  D3DXVec3Normalize(&direction, &power);
  //const float impact_power = D3DXVec3Length(&power);

  speed_ += direction * pin::lane_pin::kImpactPower;
  speed_.y = pin::lane_pin::kImpactHeight;
  int random = (rand() % 2) ? 1 : -1;
  int side_power = ( rand() % 10 );
  speed_.x = random * ( pin::lane_pin::kImpactSide * side_power );
  speed_.z += 10000.0f;
  rotation_.z = -random * ( 0.05f * side_power);
  rotation_speed_ = 0.2f;
  velocity_.y -= 9.8f * 3.0f;
  is_all_drawed_ = true;
  is_collided_ = true;
  auto h = EffectManagerServiceLocator::Get()->Play3D("EF_Game_hit", position_.x, position_.y + 100 - pin::lane_pin::kHalfSizeY, position_.z + 500);
  EffectManagerServiceLocator::Get()->SetScale(h, 100, 100, 100);
};

//------------------------------------------------
// Reset
//------------------------------------------------
void LanePin::Reset(void) {
  Pin::Reset();
  rotation_speed_ = 0.0f;
  theta_ = initial_theta_;
  EffectManagerServiceLocator::Get()->Stop3D(handle_);
  handle_ = EffectManagerServiceLocator::Get()->Play3D(kBoostEffectName, position_.x, position_.y - pin::lane_pin::kHalfSizeY, position_.z);
  EffectManagerServiceLocator::Get()->SetScale(handle_, kEffectScale, kEffectScale, kEffectScale);
  sum_time_ = 0;
}

//------------------------------------------------
// _Update
//------------------------------------------------
void LanePin::_Update(const float elapsed_time) {
  sum_time_ += elapsed_time;
  if( !is_collided_ ) {
    theta_ = sum_time_ * pin::lane_pin::kMovingSpeed + initial_theta_;
    position_.x = base_position_.x + sinf(theta_) * pin::lane_pin::kMovingDistance;
    //theta_ += elapsed_time * pin::lane_pin::kMovingSpeed;
  }

  if (position_.x > 2200.0f || position_.x < -2200.0f) {
    return;
  }
  Pin::_Update(elapsed_time);

  D3DXVECTOR3 effect_position = position_;
  effect_position.y -= ( 50.0f + pin::lane_pin::kHalfSizeY );
  EffectManagerServiceLocator::Get()->SetPosition(handle_, effect_position);

  rotation_.x += rotation_speed_;
}