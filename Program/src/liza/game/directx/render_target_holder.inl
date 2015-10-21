//==============================================================================
//
// レンダーターゲット保持クラス
// Author : Shimizu Shoji
//
// レンダーターゲットに関わるテクスチャ、サーフェイス及びビューポートを保持する
// また、描画機構への簡単な割り当てもサポート
// 
//==============================================================================
#pragma once
#ifndef __INL_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_INL__
#define __INL_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_INL__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "render_target_holder.h"

#include <assert.h>

#include <liza/SafeRelease.h>

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
inline
liza::game::directx::RenderTargetHolder::RenderTargetHolder(
    LPDIRECT3DDEVICE9 p_device, const unsigned int width, const unsigned int height)
    : p_device_(p_device)
    , p_texture_(nullptr)
    , p_surface_(nullptr)
    , p_depth_buffer_(nullptr)
    , p_texture_old_(nullptr)
    , p_surface_old_(nullptr)
    , p_depth_buffer_old_(nullptr)
    , is_assigned_(false) {
  // create texture
  HRESULT hr = p_device_->CreateTexture(
    width,
    height,
    1,
    D3DUSAGE_RENDERTARGET,
    D3DFMT_A8R8G8B8,
    D3DPOOL_DEFAULT,
    &p_texture_,
    nullptr);
  if (FAILED(hr)) {
    MessageBox(nullptr, "Failed to create a texture.", "Error", MB_OK);
  }

  // create surface
  hr = p_texture_->GetSurfaceLevel(0, &p_surface_);
  if (FAILED(hr)) {
    MessageBox(nullptr, "Failed to create a surface.", "Error", MB_OK);
  }

  // create depth buffer
  // ステンシルサーフェイスの作成
  hr = p_device_->CreateDepthStencilSurface(
    width,
    height,
    D3DFMT_D16,
    D3DMULTISAMPLE_NONE,
    0,
    TRUE,
    &p_depth_buffer_,
    nullptr);
  if (FAILED(hr)) {
    MessageBox(nullptr, "Failed to create a stencil surface.", "Error", MB_OK);
  }

  // viewport setting
  viewport_.X = 0;
  viewport_.Y = 0;
  viewport_.Width = width;
  viewport_.Height = height;
  viewport_.MinZ = 0.0f;
  viewport_.MaxZ = 1.0f;
}

//------------------------------------------------
// dtor
//------------------------------------------------
inline
liza::game::directx::RenderTargetHolder::~RenderTargetHolder() {
  SafeRelease(p_depth_buffer_);
  SafeRelease(p_surface_);
  SafeRelease(p_texture_);
}

//------------------------------------------------
// テクスチャ、サーフェイス及びビューポートを描画機構に割り当てる
// 使い終わったら割り当てを解除すること
// 直前に割り当てられていたものは保存され、割り当て解除時に自動的に再割り当てされる
//------------------------------------------------
inline
void liza::game::directx::RenderTargetHolder::AssignRenderTarget(void) {
  // guard
  assert(!is_assigned_);
  if (is_assigned_) {
    return;
  }

  // save render target
  p_device_->GetRenderTarget(0, &p_surface_old_);
  p_device_->GetDepthStencilSurface(&p_depth_buffer_old_);
  p_device_->GetViewport(&viewport_old_);

  // assign render target
  p_device_->SetRenderTarget(0, p_surface_);
  p_device_->SetDepthStencilSurface(p_depth_buffer_);
  p_device_->SetViewport(&viewport_);

  is_assigned_ = true;
}

//------------------------------------------------
// テクスチャ、サーフェイス及びビューポートの描画機構への割り当てを解除
//------------------------------------------------
inline
void liza::game::directx:: RenderTargetHolder::UnAssignRenderTarget(void) {
  // guard
  assert(is_assigned_);
  if (!is_assigned_) {
    return;
  }

  // unassign render target
  p_device_->SetRenderTarget(0, p_surface_old_);
  p_device_->SetDepthStencilSurface(p_depth_buffer_old_);
  p_device_->SetViewport(&viewport_old_);
  SafeRelease(p_surface_old_);
  SafeRelease(p_depth_buffer_old_);

  is_assigned_ = false;
}

//------------------------------------------------
// レンダーターゲットに割り当てていた場合はそのままクリア
// 割り当てていなかった場合は割り当ててクリアして割り当てを解除する
// なんにせよ中身をクリアする
//------------------------------------------------
inline
void liza::game::directx::RenderTargetHolder::Clear(void) {
  if (is_assigned_) {
    p_device_->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 0xffffffff, 1.0f, 0L);
  }
  else {
    AssignRenderTarget();
    Clear();
    UnAssignRenderTarget();
  }
}

#endif  // __INL_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_INL__
