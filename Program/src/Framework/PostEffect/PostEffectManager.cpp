//==============================================================================
//
// PostEffectManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "PostEffectManager.h"

#include "ColorGrading/ColorGrading.h"
#include "Fade/FadeEffect.h"

#include "Framework/Utility/DeviceHolder.h"
#include "Framework/RenderTarget/RenderTargetManager.h"
#include "Framework/Shader/shader_manager.h"

#include "liza/game/DirectXUtility/DirectXUtility.h"

#include "window_config.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
post_effect::PostEffectManager::PostEffectManager()
    : p_shader_(nullptr) {
  p_shader_ = ShaderManager::Instance().FindShader("draw2d");
  post_effects_.push_back(new ColorGrading());
  post_effects_.push_back(new FadeEffect());
}

//------------------------------------------------
// dtor
//------------------------------------------------
post_effect::PostEffectManager::~PostEffectManager() {
  for (auto p_post_effect : post_effects_) {
    SafeDelete(p_post_effect);
  }
}

//------------------------------------------------
// Process
//------------------------------------------------
void post_effect::PostEffectManager::Process() {
  auto p_device = DeviceHolder::Instance().GetDevice();

  LPDIRECT3DTEXTURE9 p_texture = RenderTargetManager::Instance().GetTexture(0);
  //LPDIRECT3DTEXTURE9 p_sink = nullptr;
  for (auto p_post_effect : post_effects_) {
    p_texture = p_post_effect->Process(p_texture);
    //p_source = p_sink;
  }
  p_device->BeginScene();

  p_shader_->Begin(nullptr, 0);
  p_shader_->BeginPass(0);
  p_shader_->SetTexture("texture_decale", p_texture);
  DrawFullScreenQuad(p_device, 0, 0, 1, 1);
  p_shader_->EndPass();
  p_shader_->End();

  p_device->EndScene();
}
