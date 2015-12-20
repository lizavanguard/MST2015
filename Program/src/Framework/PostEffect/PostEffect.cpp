//==============================================================================
//
// PostEffect
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "PostEffect.h"

#include "Framework/Fade/Fade.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Utility/DeviceHolder.h"

#include "liza/game/DirectXUtility/DirectXUtility.h"

#include "window_config.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
post_effect::PostEffect::PostEffect(const char* p_shader_name)
    : p_render_target_(nullptr)
    , p_shader_(nullptr) {
  p_render_target_ = new liza::game::directx::RenderTargetHolder(
    DeviceHolder::Instance().GetDevice(),
    kWindowWidth,
    kWindowHeight);
  p_shader_ = ShaderManager::Instance().FindShader(p_shader_name);
}

//------------------------------------------------
// dtor
//------------------------------------------------
post_effect::PostEffect::~PostEffect() {
  SafeDelete(p_render_target_);
}

//------------------------------------------------
// Process
//------------------------------------------------
LPDIRECT3DTEXTURE9 post_effect::PostEffect::Process(LPDIRECT3DTEXTURE9 p_source) {
  p_render_target_->AssignRenderTarget(0);
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->BeginScene();

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);
  _Process(p_source);
  p_shader_->CommitChanges();
  DrawFullScreenQuad(p_device, 0.0f, 0.0f, 1.0f, 1.0f);
  p_shader_->EndPass();
  p_shader_->End();

  p_device->EndScene();
  p_render_target_->UnAssignRenderTarget();

  return p_render_target_->GetTexture();
}
