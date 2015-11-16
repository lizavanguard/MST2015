//==============================================================================
//
// DirectX�p���[�e�B���e�B [DirectXUtility.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "DirectXUtility.h"
#include <liza/SafeRelease.h>


//==============================================================================
// class implmentation
//==============================================================================
//// ctor/dtor
//TexAndSurfHolder::TexAndSurfHolder(
//	LPDIRECT3DDEVICE9 pDevice,
//	unsigned int width,
//	unsigned int height,
//	D3DFORMAT format
//) : pTex( nullptr ), pSurf( nullptr ) {
//	CreateTextureAndSurface( pDevice, width, height, format, &pTex, &pSurf );
//}
//
//
//TexAndSurfHolder::~TexAndSurfHolder() {
//	SafeRelease( pSurf );
//	SafeRelease( pTex );
//}


//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// ���_�錾�̍쐬
//------------------------------------------------
void CreateVertexDeclaration(
	LPDIRECT3DDEVICE9 pDevice,
	D3DVERTEXELEMENT9* pElem,
	IDirect3DVertexDeclaration9** ppVertexDeclaration
) {
	HRESULT hr = pDevice->CreateVertexDeclaration( pElem, ppVertexDeclaration );
	if( FAILED( hr ) ) {
		MessageBox( nullptr, "Failed to create a vertex-declaration.", "Error", MB_OK );
	}
}


//------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//------------------------------------------------
void CreateTexture( LPDIRECT3DDEVICE9 pDevice, const char* pFilename, LPDIRECT3DTEXTURE9* ppTexture ) {
	HRESULT hr = D3DXCreateTextureFromFile( pDevice, pFilename, ppTexture );
	if( FAILED( hr ) ) {
		MessageBox( nullptr, "Failed to create a texture.", "Error", MB_OK );
	}
}


//------------------------------------------------
// �e�N�X�`���ƃT�[�t�F�C�X�̍쐬
//------------------------------------------------
void CreateTextureAndSurface(
	LPDIRECT3DDEVICE9 pDevice,
	unsigned int width,
	unsigned int height,
	D3DFORMAT format,
	LPDIRECT3DTEXTURE9* ppTexture,
	LPDIRECT3DSURFACE9* ppSurface
) {
	// create texture
	HRESULT hr = pDevice->CreateTexture(
		width,
		height,
		1,
		D3DUSAGE_RENDERTARGET,
		format,
		D3DPOOL_DEFAULT,
		ppTexture,
		nullptr
	);
	if( FAILED( hr ) ) {
		MessageBox( nullptr, "Failed to create a texture.", "Error", MB_OK );
	}

	// get surface
	hr = (*ppTexture)->GetSurfaceLevel( 0, ppSurface );
	if( FAILED( hr ) ) {
		MessageBox( nullptr, "Failed to get a texture surface.", "Error", MB_OK );
	}
}


//------------------------------------------------
// �f�v�X�X�e���V���T�[�t�F�C�X�̍쐬
//------------------------------------------------
void CreateDepthStencilSurface(
	LPDIRECT3DDEVICE9 pDevice,
	unsigned int width,
	unsigned int height,
	D3DFORMAT format,
	LPDIRECT3DSURFACE9* ppSurface
) {
	HRESULT hr = pDevice->CreateDepthStencilSurface(
		width, height, format, D3DMULTISAMPLE_NONE, 0, TRUE, ppSurface, nullptr
	);
	if( FAILED( hr ) ) {
		MessageBox( nullptr, "Failed to create a stencil buffer.", "Error", MB_OK );
	}
}


//------------------------------------------------
// Calc texture coords
//------------------------------------------------
bool CalcTextureCoords(
	CoordRect* pCoords,
	const LPDIRECT3DTEXTURE9 pTexSrc,
	const RECT* pRectSrc,
	const LPDIRECT3DTEXTURE9 pTexDest,
	const RECT* pRectDest
) {
	// �p�����[�^�̃`�F�b�N
	if( !pCoords | !pTexSrc || !pTexDest ) {
		return false;
	}

	// ��{�I�ɂ̓e�N�X�`�����W�����̂܂܏o�͂���
	pCoords->u0 = 0;
	pCoords->v0 = 0;
	pCoords->u1 = 1;
	pCoords->v1 = 1;

	// ���͌��̃T�[�t�F�X�Ɋւ��ĕ␳����
	if( pRectSrc ) {
		D3DSURFACE_DESC desc;
		pTexSrc->GetLevelDesc( 0, &desc );
		// ���͌��̋�`�ɉ����ăe�N�X�`�����W�����킹��
		pCoords->u0 += pRectSrc->left / desc.Width;
		pCoords->v0 += pRectSrc->top / desc.Height;
		pCoords->u1 -= ( desc.Width - pRectSrc->right ) / desc.Width;
		pCoords->v1 -= ( desc.Height - pRectSrc->bottom ) / desc.Height;
	}

	// �o�͐�̃T�[�t�F�X�Ɋւ��ĕ␳����
	if( pRectDest ) {
		D3DSURFACE_DESC desc;
		pTexDest->GetLevelDesc( 0, &desc );
		// �o�͐�̋�`�ɉ����ăe�N�X�`�����W�����킹��
		pCoords->u0 += pRectDest->left / desc.Width;
		pCoords->v0 += pRectDest->top / desc.Height;
		pCoords->u1 -= ( desc.Width - pRectDest->right ) / desc.Width;
		pCoords->v1 -= ( desc.Height - pRectDest->bottom ) / desc.Height;
	}

	return true;
}


//------------------------------------------------
// Calc the weight and offset used by GaussBlur5x5
//------------------------------------------------
bool CalcWeigthAndOffsetUsedByGaussBlur5x5(
	D3DXVECTOR2* pTexCoordOffsets,
	D3DXVECTOR4* pSampleWeights,
	const unsigned int texWidth,
	const unsigned int texHeight
) {
	// �e�N�Z���̑傫��
	const float tu = 1.0f / texWidth;
	const float tv = 1.0f / texHeight;

	// �d�݂ƃI�t�Z�b�g���v�Z
	float sumWeight = 0;
	unsigned int index = 0;
	for( int x = -2; x <= 2; ++x ) {
		for( int y = -2; y <= 2; ++y ) {
			// �W�����������Ȃ镔���͏���
			if( 2 < abs( x ) + abs( y ) ) {
				continue;
			}

			// �e�N�Z����ł̈ʒu(�I�t�Z�b�g)���v�Z
			pTexCoordOffsets[ index ] = D3DXVECTOR2( x * tu, y * tv );

			// �d�݂��v�Z
			pSampleWeights[ index ].x = pSampleWeights[ index ].y =
			pSampleWeights[ index ].z = pSampleWeights[ index ].w =
				expf( -( x * x + y * y ) / ( 2 * 1.0f ) );

			sumWeight += pSampleWeights[ index ].x;
			++index;
		}
	}

	// �d�݂̍��v��1�ɂ���
	for( unsigned int i = 0; i < index; ++i ) {
		pSampleWeights[ i ] *= 1.0f / sumWeight;
	}

	return true;
}


//------------------------------------------------
// Draw quad on full screen
// left-top = (su,sv)
// right-bottom = (eu,ev)
//------------------------------------------------
void DrawFullScreenQuad( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev ) {
	// �����_�����O�^�[�Q�b�g�̃T�C�Y���擾����
	LPDIRECT3DSURFACE9 pSurf;
	pDevice->GetRenderTarget( 0, &pSurf );
	D3DSURFACE_DESC desc;
	pSurf->GetDesc( &desc );
	pSurf->Release();
	float w = (float)desc.Width;
	float h = (float)desc.Height;

	// ��`����
	struct _ScreenVertex { float p[ 4 ]; float t[ 2 ]; };
	_ScreenVertex quad[ 4 ] = {
		//       x,        y,    z,    w,  u,  v
		{ 0 - 0.5f, 0 - 0.5f, 0.5f, 1.0f, su, sv },
		{ w - 0.5f, 0 - 0.5f, 0.5f, 1.0f, eu, sv },
		{ 0 - 0.5f, h - 0.5f, 0.5f, 1.0f, su, ev },
		{ w - 0.5f, h - 0.5f, 0.5f, 1.0f, eu, ev },
	};

	// �`��
	pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_TEX1 );
	pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, quad, sizeof( _ScreenVertex ) );
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
}


//------------------------------------------------
// Draw quad on full screen on local
// �ˉe�ϊ��͂�����Ȃ�
// ���̏�ŉ�ʂ����ς��̃|���S�����`�悳���
// ���_�V�F�[�_��ʂ��������͂���������
//------------------------------------------------
void DrawFullScreenQuadOnLocal( LPDIRECT3DDEVICE9 pDevice, float su, float sv, float eu, float ev ) {
	// ��`����
	struct _ScreenVertex { float p[ 3 ]; float t[ 2 ]; };
	_ScreenVertex quad[ 4 ] = {
		{ -1.0f, +1.0f, 0.1f, su, sv },
		{ +1.0f, +1.0f, 0.1f, eu, sv },
		{ -1.0f, -1.0f, 0.1f, su, ev },
		{ +1.0f, -1.0f, 0.1f, eu, ev },
	};

	// �`��
	pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
	pDevice->SetFVF( D3DFVF_XYZ | D3DFVF_TEX1 );
	pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, quad, sizeof( _ScreenVertex ) );
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
}