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
  const float kAualaEffectScale = 180.0f;
  const char* kFallEffectName = "EF_Game_BigPinBreak";
  const float kFallEffectScale = 300.0f;
  const char* kHitEffectName = "EF_Game_Pin_Gold_Crash";
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
, animation_num_(0)
, fall_flg_(false) {
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
  rotation_speed_.x = kFallingSpeed;
  animation_count_++;
  animation_num_ = 0;
  is_all_drawed_ = true;
  is_collided_ = true;
  handle_hit_ = EffectManagerServiceLocator::Get()->Play3D(kHitEffectName, power.x, power.y + 100.0f, power.z);
  EffectManagerServiceLocator::Get()->SetScale(handle_hit_, kHitEffectScale, kHitEffectScale, kHitEffectScale);
  EffectManagerServiceLocator::Get()->Stop3D(handle_);
};

void BiggestPin::FallCollision(void) {
  fall_flg_ = true;
}

//------------------------------------------------
// Reset
//------------------------------------------------
void BiggestPin::Reset(void) {
  Pin::Reset();
  rotation_speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  animation_count_ = 0;
  animation_num_ = 0;
  fall_flg_ = false;
}

//------------------------------------------------
// _Update
//------------------------------------------------
void BiggestPin::_Update(const float elapsed_time) {
  Pin::_Update(elapsed_time);
  if( !is_collided_ ) return;
  animation_count_++;
  if( animation_count_ > 0 && animation_count_ < 124 ) {
    if( animation_count_ < 5 ) {
      animation_num_++;
      animation_num_ %= 2;
    } else if( animation_count_ % 10 == 0 ) {
      animation_num_++;
      animation_num_ %= 2;
    }
    rotation_.x += kFallingRotation[animation_num_] * 0.025f;
    position_.z += kFallingPositionY;
  } else if( fall_flg_ ) {
    if( rotation_.x < D3DX_PI * 0.5f ) {
      rotation_ += rotation_speed_;
      position_.y += kFallingPositionY;
      if( rotation_.x >= D3DX_PI * 0.5f ) {
        EffectManagerServiceLocator::Get()->Stop3D(handle_);
        handle_fall_ = EffectManagerServiceLocator::Get()->Play3D(kFallEffectName, position_.x, position_.y - 1500.0f, position_.z + 1000.0f);
        EffectManagerServiceLocator::Get()->SetScale(handle_fall_, kFallEffectScale, kFallEffectScale, kFallEffectScale);
      }
    }
  }
}
