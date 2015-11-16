//==============================================================================
//
// DirectX用ユーティリティ [DirectXUtility.h]
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
// 矩形
//------------------------------------------------
struct CoordRect {
  float u0, v0;
  float u1, v1;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// 頂点宣言の作成
//------------------------------------------------
inline
void CreateVertexDeclaration(
	LPDIRECT3DDEVICE9 pDevice,
	D3DVERTEXELEMENT9* pElem,
	IDirect3DVertexDeclaration9** ppVertexDeclaration
);


//------------------------------------------------
// テクスチャの読み込み
//------------------------------------------------
inline
void CreateTexture(LPDIRECT3DDEVICE9 pDevice, const char* pFilename, LPDIRECT3DTEXTURE9* ppTexture);


//------------------------------------------------
// テクスチャとサーフェイスの作成
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
// デプスステンシルサーフェイスの作成
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
// テクスチャ座標の計算
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
// 重みとガウスブラーの係数計算
//------------------------------------------------
inline
bool CalcWeigthAndOffsetUsedByGaussBlur5x5(
	D3DXVECTOR2* pTexCoordOffsets,
	D3DXVECTOR4* pSampleWeights,
	unsigned int texWidth,
	unsigned int texHeight
);


//------------------------------------------------
// 矩形をスクリーン上に描画
// left-top = (su,sv)
// right-bottom = (eu,ev)
//------------------------------------------------
inline
void DrawFullScreenQuad( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev );


//------------------------------------------------
// 矩形をスクリーン上に描画
// 射影変換はかからない
// その上で画面いっぱいのポリゴンが描画される
// 頂点シェーダを通したい時はこっちかな
//------------------------------------------------
inline
void DrawFullScreenQuadOnLocal( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// テクスチャとサーフェイス保持クラス
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