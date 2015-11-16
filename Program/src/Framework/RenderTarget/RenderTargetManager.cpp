//==============================================================================
//
// RenderTargetManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "RenderTargetManager.h"

#include "Framework/Utility/DeviceHolder.h"

#include "liza/game/directx/render_target_holder.h"

#include "window_config.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_RenderTargetManager::_RenderTargetManager(const unsigned int num_render_targets)
    : num_render_targets_(num_render_targets) {
  static const unsigned int kRenderTargetMax = 4;  // ‚È‚ñ‚Æ‚È‚­
  MY_BREAK_MAX_ASSERT(num_render_targets_, kRenderTargetMax);

  container_.reserve(num_render_targets_);
  auto p_device = DeviceHolder::Instance().GetDevice();
  for (unsigned int render_target_count = 0; render_target_count < num_render_targets_; ++render_target_count) {
    container_.push_back(new liza::game::directx::RenderTargetHolder(p_device, kWindowWidth, kWindowHeight));
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
_RenderTargetManager::~_RenderTargetManager() {
  for (unsigned int render_target_count = 0; render_target_count < num_render_targets_; ++render_target_count) {
    SafeDelete(container_[render_target_count]);
  }
}

//------------------------------------------------
// Assign render target
//------------------------------------------------
void _RenderTargetManager::Assign(void) {
  for (unsigned int render_target_count = 0; render_target_count < num_render_targets_; ++render_target_count) {
    auto& render_target = container_[render_target_count];
    render_target->AssignRenderTarget(render_target_count);
  }
}

//------------------------------------------------
// UnAssign
//------------------------------------------------
void _RenderTargetManager::UnAssign(void) {
  for (unsigned int render_target_count = 0; render_target_count < num_render_targets_; ++render_target_count) {
    auto& render_target = container_[render_target_count];
    render_target->UnAssignRenderTarget();
  }
}

//------------------------------------------------
// Clear
//------------------------------------------------
void _RenderTargetManager::Clear(void) {
  for (unsigned int render_target_count = 0; render_target_count < num_render_targets_; ++render_target_count) {
    auto& render_target = container_[render_target_count];
    render_target->Clear();
  }
}

//------------------------------------------------
// Get texture
//------------------------------------------------
LPDIRECT3DTEXTURE9 _RenderTargetManager::GetTexture(unsigned int index) const {
  if (!_CheckIndex(index)) {
    return nullptr;
  }
  return container_[index]->GetTexture();
}

//------------------------------------------------
// check index
// if 'index' is more than 'num_render_targets' : false
// else : true
//------------------------------------------------
bool _RenderTargetManager::_CheckIndex(unsigned int index) const {
  MY_BREAK_MAX_ASSERT(index, num_render_targets_);
  return index < num_render_targets_;
}
