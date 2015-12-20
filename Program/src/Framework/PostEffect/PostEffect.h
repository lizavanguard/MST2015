//==============================================================================
//
// PostEffect
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/game/directx/render_target_holder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace post_effect {

class PostEffect {
public:
  // ctor
  PostEffect(const char* p_shader_name);

  // dtor
  virtual ~PostEffect();

  // Process
  LPDIRECT3DTEXTURE9 Process(LPDIRECT3DTEXTURE9 p_source);

  // get
  liza::game::directx::RenderTargetHolder* GetRenderTarget() const { return p_render_target_; }
  LPD3DXEFFECT GetShader() const { return p_shader_; }

private:
  // _Process
  virtual void _Process(LPDIRECT3DTEXTURE9 p_source) = 0;

  // property
  liza::game::directx::RenderTargetHolder* p_render_target_;
  LPD3DXEFFECT p_shader_;
};

}  // namespace post_effect
