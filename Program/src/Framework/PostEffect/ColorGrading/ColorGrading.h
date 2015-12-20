//==============================================================================
//
// ColorGrading
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/PostEffect/PostEffect.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace post_effect {

class ColorGrading : public PostEffect {
public:
  // ctor
  ColorGrading();

  // dtor
  virtual ~ColorGrading();

private:
  // _Process
  virtual void _Process(LPDIRECT3DTEXTURE9 p_source) override;
  D3DXVECTOR3 ycbcr;
  bool is_applied_;
};

}  // namespace post_effect
