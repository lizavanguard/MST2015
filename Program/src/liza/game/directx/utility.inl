//==============================================================================
//
// DirectX�p���[�e�B���e�B
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZA_GAME_DIRECTX_UTILITY_INL__
#define __INL_LIZA_GAME_DIRECTX_UTILITY_INL__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "utility.h"

#include <assert.h>
#include <list>

//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// �f�o�b�O�p�̃`�F�b�N�֐�
// �G���[�ϐ���null������P�[�X�����̂Ƃ���Y���t�@�C�����Ȃ��ꍇ�݂̂Ȃ̂ŁB
//------------------------------------------------
inline bool _CheckSucceeded(HRESULT hr, LPD3DXBUFFER p_error) {
  return SUCCEEDED(hr) ||
         !MessageBox(nullptr, (p_error ? (LPCTSTR)p_error->GetBufferPointer() : "This file does not exist."), "Error", MB_OK);
}

//------------------------------------------------
// �V�F�[�_�̃��[�h���s��
// �|�C���^��n���Ɗi�[���Ė߂�
//------------------------------------------------
inline
void liza::game::directx::LoadShader(LPDIRECT3DDEVICE9 p_device, const char* p_filename, LPD3DXEFFECT* pp_effect) {
  LPD3DXBUFFER p_error = nullptr;
  HRESULT hr = D3DXCreateEffectFromFile(
    p_device,
    p_filename,
    nullptr,
    nullptr,
    0,
    nullptr,
    pp_effect,
    &p_error);
  assert(_CheckSucceeded(hr, p_error));
}

//------------------------------------------------
// ���b�V���̃��[�h���s��
// �����ōœK�����s��
//------------------------------------------------
inline
void liza::game::directx::LoadMeshFromX(
    LPDIRECT3DDEVICE9 p_device,
    const char* p_filename,
    LPD3DXMESH* pp_mesh,
    LPD3DXBUFFER* pp_material,
    DWORD* p_num_material) {
  LPD3DXBUFFER p_adjacency_buffer = nullptr;
  HRESULT hr = D3DXLoadMeshFromX(
    p_filename,
    D3DXMESH_SYSTEMMEM,
    p_device,
    &p_adjacency_buffer,
    pp_material,
    nullptr,
    p_num_material,
    pp_mesh);
  assert(SUCCEEDED(hr) || !MessageBox(nullptr, "Failed to load a mesh from x-file.", "Error", MB_OK));

  hr = (*pp_mesh)->OptimizeInplace(
    D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
    (DWORD*)(p_adjacency_buffer->GetBufferPointer()),
    nullptr,
    nullptr,
    nullptr);
  p_adjacency_buffer->Release();
  assert(SUCCEEDED(hr) || !MessageBox(nullptr, "Failed to optimize a mesh.", "Error", MB_OK));
}

//------------------------------------------------
// ���b�V���ɒ��_�錾�̏��𖄂ߍ���
//------------------------------------------------
inline
void liza::game::directx::AttachVertexDeclarationToMesh(
    LPDIRECT3DDEVICE9 p_device,
    LPD3DXMESH* pp_mesh,
    D3DVERTEXELEMENT9* p_elements) {
  LPD3DXMESH p_old_mesh = *pp_mesh;
  HRESULT hr = p_old_mesh->CloneMesh(D3DXMESH_MANAGED, p_elements, p_device, pp_mesh);
  p_old_mesh->Release();
  assert(SUCCEEDED(hr) || !MessageBox(nullptr, "Failed to clone mesh.", "Error", MB_OK));
}

//------------------------------------------------
// �f�o�b�O�p�̍\���̎擾
//------------------------------------------------
inline
std::list<LPDIRECT3DTEXTURE9>& _GetTextureDebugInstance(void) {
  static std::list<LPDIRECT3DTEXTURE9> instance;
  return instance;
}

//------------------------------------------------
// �f�o�b�O�p�֐�
// ���g���m�F�������e�N�X�`����n��
// �`�悷��ꍇ�́A�m�F�������S�Ẵe�N�X�`����n�������
// �Ή������`��֐����Ă�
//------------------------------------------------
inline
void liza::game::directx::AddTextureDebug(LPDIRECT3DTEXTURE9 p_texture) {
#ifdef _DEBUG
  _GetTextureDebugInstance().push_back(p_texture);
#endif
}

//------------------------------------------------
// �f�o�b�O�p�֐�
// �Ή�����ǉ��֐��ɂ��n���ꂽ�e�N�X�`������ʍ���ɕ`�悷��
// �n���ꂽ���Ԃɍ��ォ�獶���ɕ��ׂĕ`�悳���
//------------------------------------------------
inline
void liza::game::directx::DrawTextureDebug(LPDIRECT3DDEVICE9 p_device) {
#ifdef _DEBUG
  static const float kScale = 128.0f;  // �Ȃ�ƂȂ�

  // save pre-set status
  DWORD color_op0_old = 0;
  DWORD color_arg0_old = 0;
  DWORD color_op1_old = 0;
  p_device->GetTextureStageState(0, D3DTSS_COLOROP, &color_op0_old);
  p_device->GetTextureStageState(0, D3DTSS_COLORARG1, &color_arg0_old);
  p_device->GetTextureStageState(1, D3DTSS_COLOROP, &color_op1_old);
  LPDIRECT3DVERTEXSHADER9 vertex_shader_old;
  LPDIRECT3DPIXELSHADER9 pixel_shader_old;
  p_device->GetVertexShader(&vertex_shader_old);
  p_device->GetPixelShader(&pixel_shader_old);
  DWORD fvf_old;
  p_device->GetFVF(&fvf_old);

  // set status
  p_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
  p_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
  p_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);

  p_device->SetVertexShader(nullptr);
  p_device->SetPixelShader(nullptr);

  p_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

  struct _CustomVertex {
    float x, y, z, rhw, tu, tv;
  };

  unsigned int count = 0;
  auto& texture_list = _GetTextureDebugInstance();
  for (auto p_texture : texture_list) {
    const float top = kScale * count;
    const float bottom = kScale * (count + 1);
    _CustomVertex vertices[4] = {
      //    x       y  z rhw tu tv
      {     0,    top, 0, 1, 0, 0},
      {kScale,    top, 0, 1, 1, 0},
      {kScale, bottom, 0, 1, 1, 1},
      {     0, bottom, 0, 1, 0, 1},
    };

    p_device->SetTexture(0, p_texture);
    p_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(_CustomVertex));

    ++count;
  }

  texture_list.clear();

  p_device->SetFVF(fvf_old);
  p_device->SetPixelShader(pixel_shader_old);
  p_device->SetVertexShader(vertex_shader_old);
  p_device->SetTextureStageState(1, D3DTSS_COLOROP, color_op1_old);
  p_device->SetTextureStageState(0, D3DTSS_COLORARG0, color_arg0_old);
  p_device->SetTextureStageState(0, D3DTSS_COLOROP, color_op0_old);

#endif
}

#endif // __INL_LIZA_GAME_DIRECTX_UTILITY_INL__
