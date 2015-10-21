//=========================================o=====================================
//
// DirectX�p���[�e�B���e�B
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZA_GAME_DIRECTX_UTILITY_H__
#define __H_LIZA_GAME_DIRECTX_UTILITY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <d3dx9.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
namespace game {
namespace directx {

//------------------------------------------------
// �V�F�[�_�̃��[�h���s��
// �|�C���^��n���Ɗi�[���Ė߂�
//------------------------------------------------
void LoadShader(LPDIRECT3DDEVICE9 p_device, const char* p_filename, LPD3DXEFFECT* pp_effect);

//------------------------------------------------
// ���b�V���̃��[�h���s��
// �����ōœK�����s��
//------------------------------------------------
void LoadMeshFromX(
    LPDIRECT3DDEVICE9 p_device,
    const char* p_filename,
    LPD3DXMESH* pp_mesh,
    LPD3DXBUFFER* pp_material,
    DWORD* p_num_material);

//------------------------------------------------
// ���b�V���ɒ��_�錾�̏��𖄂ߍ���
//------------------------------------------------
void AttachVertexDeclarationToMesh(
    LPDIRECT3DDEVICE9 p_device,
    LPD3DXMESH* pp_mesh,
    D3DVERTEXELEMENT9* p_elements);

//------------------------------------------------
// �f�o�b�O�p�֐�
// ���g���m�F�������e�N�X�`����n��
// �`�悷��ꍇ�́A�m�F�������S�Ẵe�N�X�`����n�������
// �Ή������`��֐����Ă�
//------------------------------------------------
void AddTextureDebug(LPDIRECT3DTEXTURE9 p_texture);

//------------------------------------------------
// �f�o�b�O�p�֐�
// �Ή�����ǉ��֐��ɂ��n���ꂽ�e�N�X�`������ʍ���ɕ`�悷��
// �n���ꂽ���Ԃɍ��ォ�獶���ɕ��ׂĕ`�悳���
//------------------------------------------------
void DrawTextureDebug(LPDIRECT3DDEVICE9 p_device);

}  // namespace directx
}  // namespace game
}  // liza

// inline header
#include "utility.inl"

#endif // __H_LIZA_GAME_DIRECTX_UTILITY_H__
