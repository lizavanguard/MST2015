//==============================================================================
//
// DirectX�p���[�e�B���e�B [DirectXUtility.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_DIRECTXUTILITY_H__
#define __H_DIRECTXUTILITY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <d3dx9.h>

//------------------------------------------------
// ��`
//------------------------------------------------
struct CoordRect {
  float u0, v0;
  float u1, v1;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ���_�錾�̍쐬
//------------------------------------------------
inline
void CreateVertexDeclaration(
	LPDIRECT3DDEVICE9 pDevice,
	D3DVERTEXELEMENT9* pElem,
	IDirect3DVertexDeclaration9** ppVertexDeclaration
);


//------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//------------------------------------------------
inline
void CreateTexture(LPDIRECT3DDEVICE9 pDevice, const char* pFilename, LPDIRECT3DTEXTURE9* ppTexture);


//------------------------------------------------
// �e�N�X�`���ƃT�[�t�F�C�X�̍쐬
//------------------------------------------------
inline
void CreateTextureAndSurface(
	LPDIRECT3DDEVICE9 pDevice,
	unsigned int width,
	unsigned int height,
	D3DFORMAT format,
	LPDIRECT3DTEXTURE9* ppTexture,
	LPDIRECT3DSURFACE9* ppSurface
);


//------------------------------------------------
// �f�v�X�X�e���V���T�[�t�F�C�X�̍쐬
//------------------------------------------------
inline
void CreateDepthStencilSurface(
	LPDIRECT3DDEVICE9 pDevice,
	unsigned int width,
	unsigned int height,
	D3DFORMAT format,
	LPDIRECT3DSURFACE9* ppSurface
);


//------------------------------------------------
// �e�N�X�`�����W�̌v�Z
//------------------------------------------------
inline
bool CalcTextureCoords(
	CoordRect* pCoords,
	const LPDIRECT3DTEXTURE9 pTexSrc,
	const RECT* pRectSrc,
	const LPDIRECT3DTEXTURE9 pTexDest,
	const RECT* pRectDest
);


//------------------------------------------------
// �d�݂ƃK�E�X�u���[�̌W���v�Z
//------------------------------------------------
inline
bool CalcWeigthAndOffsetUsedByGaussBlur5x5(
	D3DXVECTOR2* pTexCoordOffsets,
	D3DXVECTOR4* pSampleWeights,
	unsigned int texWidth,
	unsigned int texHeight
);


//------------------------------------------------
// ��`���X�N���[����ɕ`��
// left-top = (su,sv)
// right-bottom = (eu,ev)
//------------------------------------------------
inline
void DrawFullScreenQuad( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev );


//------------------------------------------------
// ��`���X�N���[����ɕ`��
// �ˉe�ϊ��͂�����Ȃ�
// ���̏�ŉ�ʂ����ς��̃|���S�����`�悳���
// ���_�V�F�[�_��ʂ��������͂���������
//------------------------------------------------
inline
void DrawFullScreenQuadOnLocal( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// �e�N�X�`���ƃT�[�t�F�C�X�ێ��N���X
//------------------------------------------------
struct TexAndSurfHolder {
  // ctor
  TexAndSurfHolder(
    LPDIRECT3DDEVICE9 pDevice,
    unsigned int width,
    unsigned int height,
    D3DFORMAT format)
    : pTex(nullptr), pSurf(nullptr) {
    CreateTextureAndSurface(pDevice, width, height, format, &pTex, &pSurf);
  }

  // dtor
  ~TexAndSurfHolder() {
    SafeRelease(pSurf);
    SafeRelease(pTex);
  }

  // property
  LPDIRECT3DTEXTURE9 pTex;
  LPDIRECT3DSURFACE9 pSurf;
};

// inline
#include "DirectXUtility.inl"


#endif // __H_DIRECTXUTILITY_H__