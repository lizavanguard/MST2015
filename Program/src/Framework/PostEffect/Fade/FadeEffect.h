//==============================================================================
//
// FadeEffect
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

class FadeEffect : public PostEffect {
public:
  // ctor
  FadeEffect();

  // dtor
  virtual ~FadeEffect();

private:
  // _Process
  virtual void _Process(LPDIRECT3DTEXTURE9 p_source) override;
};

}  // namespace post_effect
