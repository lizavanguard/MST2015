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
#ifndef __H_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_H__
#define __H_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <d3dx9.h>

#include <liza/generic/noncopyable.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
namespace game {
namespace directx {

// ヘッダを参照
class RenderTargetHolder : public liza::generic::NonCopyable<RenderTargetHolder> {
public:
  // ctor
  RenderTargetHolder(LPDIRECT3DDEVICE9 p_device, unsigned int width, unsigned int height);

  // dtor
  ~RenderTargetHolder();

  // テクスチャ、サーフェイス及びビューポートを描画機構に割り当てる
  // 使い終わったら割り当てを解除すること
  // 直前に割り当てられていたものは保存され、割り当て解除時に自動的に再割り当てされる
  void AssignRenderTarget(unsigned int render_target_index);

  // テクスチャ、サーフェイス及びビューポートの描画機構への割り当てを解除
  void UnAssignRenderTarget(void);

  // レンダーターゲットに割り当てていた場合はそのままクリア
  // 割り当てていなかった場合は割り当ててクリアして割り当てを解除する
  // なんにせよ中身をクリアする
  void Clear(void);

  // get
  LPDIRECT3DTEXTURE9 GetTexture(void) const { return p_texture_; }
  unsigned int GetWidth(void) const { return viewport_.Width; }
  unsigned int GetHeight(void) const { return viewport_.Height; }

public:
  LPDIRECT3DDEVICE9 p_device_;

  LPDIRECT3DTEXTURE9 p_texture_;
  LPDIRECT3DSURFACE9 p_surface_;
  LPDIRECT3DSURFACE9 p_depth_buffer_;
  D3DVIEWPORT9 viewport_;

  LPDIRECT3DTEXTURE9 p_texture_old_;
  LPDIRECT3DSURFACE9 p_surface_old_;
  LPDIRECT3DSURFACE9 p_depth_buffer_old_;
  D3DVIEWPORT9 viewport_old_;

  unsigned int render_target_index_;

  bool is_assigned_;
};

}  // namespace directx
}  // namespace game
}  // namespace liza

// inline header
#include "render_target_holder.inl"

#endif  // __H_LIZA_GAME_DIRECTX_RENDERTARGETHOLDER_H__
