//==============================================================================
//
// Pin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Pin.h"
#include "PinConfig.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 75.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Pin::Pin(const D3DXVECTOR3& position)
    : ObjectModel(pin::kModelName)
    , CollisionObject(kSize)
    , initial_position_(position) {
  position_ = position;
}

//------------------------------------------------
// dtor
//------------------------------------------------
Pin::~Pin() {
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Pin::Reset(void) {
  position_ = initial_position_;
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  is_all_drawed_ = true;
  is_collided_ = false;
}


//------------------------------------------------
// Update
//------------------------------------------------
void Pin::_Update(const float elapsed_time) {
  velocity_ *= 0.998f;
  speed_ += velocity_;
  speed_ *= 0.998f;
  position_ += speed_ * elapsed_time;
}
