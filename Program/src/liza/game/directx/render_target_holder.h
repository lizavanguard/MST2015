//==============================================================================
//
// �����_�[�^�[�Q�b�g�ێ��N���X
// Author : Shimizu Shoji
//
// �����_�[�^�[�Q�b�g�Ɋւ��e�N�X�`���A�T�[�t�F�C�X�y�уr���[�|�[�g��ێ�����
// �܂��A�`��@�\�ւ̊ȒP�Ȋ��蓖�Ă��T�|�[�g
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

// �w�b�_���Q��
class RenderTargetHolder : public liza::generic::NonCopyable<RenderTargetHolder> {
public:
  // ctor
  RenderTargetHolder(LPDIRECT3DDEVICE9 p_device, unsigned int width, unsigned int height);

  // dtor
  ~RenderTargetHolder();

  // �e�N�X�`���A�T�[�t�F�C�X�y�уr���[�|�[�g��`��@�\�Ɋ��蓖�Ă�
  // �g���I������犄�蓖�Ă��������邱��
  // ���O�Ɋ��蓖�Ă��Ă������͕̂ۑ�����A���蓖�ĉ������Ɏ����I�ɍĊ��蓖�Ă����
  void AssignRenderTarget(unsigned int render_target_index);

  // �e�N�X�`���A�T�[�t�F�C�X�y�уr���[�|�[�g�̕`��@�\�ւ̊��蓖�Ă�����
  void UnAssignRenderTarget(void);

  // �����_�[�^�[�Q�b�g�Ɋ��蓖�ĂĂ����ꍇ�͂��̂܂܃N���A
  // ���蓖�ĂĂ��Ȃ������ꍇ�͊��蓖�ĂăN���A���Ċ��蓖�Ă���������
  // �Ȃ�ɂ��撆�g���N���A����
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
