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

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kModelname = "ball";
  const float kSize = 3.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Pin::Pin(const D3DXVECTOR3& position)
    : ObjectModel(kModelname) {
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
  position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  is_all_drawed_ = true;
}

//------------------------------------------------
// Get
//------------------------------------------------
float Pin::GetSize(void) const {
  return kSize;
}