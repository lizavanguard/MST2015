//==============================================================================
//
// BiggestPin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "BiggestPin.h"
#include "PinConfig.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kFallingSpeed = 0.01f;
  const float kFallingRotation[2] = {
    D3DX_PI * 0.1f,
    -D3DX_PI * 0.1f,
  };
  const float kFallingPositionY = 9.5f;
}

namespace {
  const char* kAualaEffectName = "EF_Game_bigPinAura";
  const float kAualaEffectScale = 60.0f;
  const char* kFallEffectName = "EF_Game_bigPinBreak";
  const float kFallEffectScale = 100.0f;
  const char* kHitEffectName = "BigHit";
  const float kHitEffectScale = 60.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
BiggestPin::BiggestPin(const D3DXVECTOR3& position) : Pin(position, pin::kBigModelName), rotation_speed_(0.0f, 0.0f, 0.0f)
, animation_count_(0)
, animation_num_(0) {
  handle_ = EffectManagerServiceLocator::Get()->Play3D(kAualaEffectName, position_.x, position_.y, position_.z);
  EffectManagerServiceLocator::Get()->SetScale(handle_, kAualaEffectScale, kAualaEffectScale, kAualaEffectScale);
}

//------------------------------------------------
// dtor
//------------------------------------------------
BiggestPin::~BiggestPin() {
}

//------------------------------------------------
// React collision
//------------------------------------------------
void BiggestPin::ReactCollision(const D3DXVECTOR3& power) {
  //D3DXVECTOR3 direction;
  //D3DXVec3Normalize(&direction, &power);
  rotation_speed_.x = kFallingSpeed;
  animation_count_++;
  animation_num_ = 0;
  is_all_drawed_ = true;
  is_collided_ = true;
  handle_hit_ = EffectManagerServiceLocator::Get()->Play3D(kHitEffectName, position_.x, position_.y + 300.0f, position_.z - 1000.0f);
  EffectManagerServiceLocator::Get()->SetScale(handle_hit_, kHitEffectScale, kHitEffectScale, kHitEffectScale);
};

//------------------------------------------------
// Reset
//------------------------------------------------
void BiggestPin::Reset(void) {
  Pin::Reset();
  rotation_speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  animation_count_ = 0;
  animation_num_ = 0;
}

//------------------------------------------------
// _Update
//------------------------------------------------
void BiggestPin::_Update(const float elapsed_time) {
  Pin::_Update(elapsed_time);
  if( !is_collided_ ) return;
  animation_count_++;
  if( animation_count_ > 0 && animation_count_ < 120 ) {
    if( animation_count_ < 5 ) {
      animation_num_++;
      animation_num_ %= 2;
    } else if( animation_count_ % 10 == 0 ) {
      animation_num_++;
      animation_num_ %= 2;
    }
    rotation_.x += kFallingRotation[animation_num_] * 0.025f;
    position_.z += kFallingPositionY;
  } else {
    if( rotation_.x < D3DX_PI * 0.5f ) {
      rotation_ += rotation_speed_;
      position_.y += kFallingPositionY;
      if( rotation_.x >= D3DX_PI * 0.5f ) {
        EffectManagerServiceLocator::Get()->Stop3D(handle_);
        handle_fall_ = EffectManagerServiceLocator::Get()->Play3D(kFallEffectName, position_.x, position_.y, position_.z);
        EffectManagerServiceLocator::Get()->SetScale(handle_fall_, kFallEffectScale, kFallEffectScale, kFallEffectScale);
      }
    }
  }
}
