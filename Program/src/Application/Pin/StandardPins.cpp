//==============================================================================
//
// StandardPins
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "StandardPins.h"

#include "StandardPin.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
StandardPins::StandardPins(const D3DXVECTOR3& center_position, const D3DXVECTOR3&) {
  static const D3DXVECTOR3 kDirection = {std::cos(D3DX_PI / 3), 0, std::sin(D3DX_PI / 3)};
  static const float kDistance = 7.5f;  // ƒsƒ“‚Æƒsƒ“‚ÌŠÔ‚Ì‹——£
  static const int kNumZ = 4;
  static const float kHeight = std::cosf(D3DX_PI / 6) * kDistance * (kNumZ - 1);
  static const float kHalfHeight = kHeight * 0.5f;

  unsigned int index = 0;
  for (int z = 0; z < kNumZ; ++z) {
    D3DXVECTOR3 base_position = kDirection * (kDistance * z);
    base_position.z -= kHalfHeight;
    for (int x = 0; x < z + 1; ++x) {
      D3DXVECTOR3 position = base_position + center_position;
      position.x -= kDistance * x;
      AttachChild(pins_[index++] = StandardPinFactory::Create(position));
    }
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
StandardPins::~StandardPins() {
}
