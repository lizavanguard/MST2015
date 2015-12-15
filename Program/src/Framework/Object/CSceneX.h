//=============================================================================
//
// シーンＸモデル処理ヘッダー [CSceneX.h]
// Author : 宗像 快
//
//=============================================================================
#pragma once
#ifndef _CSCENEX_H_
#define _CSCENEX_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "CVertexBuffer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//------------------------------
// シーンＸモデルクラス
//------------------------------
class CSceneX
{

public:
	//------------------------------
	// コンストラクタ
	// 引数：LPDIRECT3DDEVICE9 pD3DDevice
	//		 const char *pFileName		ファイル名
	//		 OBJTYPE objType			オブジェクトタイプ
	//		 int nPriority				プライオリティ
	//------------------------------
	CSceneX( LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, OBJTYPE objType = OBJTYPE_X, int nPriority = 3 );

	//------------------------------
	// デストラクタ
	//------------------------------
	~CSceneX();

	//------------------------------
	// 初期化処理
	//------------------------------
	HRESULT Init( void );

	//------------------------------
	// 終了処理
	//------------------------------
	void Uninit( void );

	//------------------------------
	// 更新処理
	//------------------------------
	void Update( void );

	//------------------------------
	// 描画処理
	//------------------------------
	void Draw( void );

	//------------------------------
	// 座標設定処理
	//------------------------------
	void SetPos( float x, float y, float z );
	void SetPos( D3DXVECTOR3 pos );

	//------------------------------
	// 座標取得処理
	//------------------------------
	D3DXVECTOR3 GetPos( void );

	//------------------------------
	// 回転設定処理
	//------------------------------
	void SetRot( float x, float y, float z );
	void SetRot( D3DXVECTOR3 rot );

	//------------------------------
	// 回転取得処理
	//------------------------------
	D3DXVECTOR3 GetRot( void );

	//------------------------------
	// テクスチャ設定処理
	//------------------------------
	void SetTexture( CTexture::TEXTURE_TYPE type );

	//------------------------------
	// CSceneX生成処理
	// 引数：LPDIRECT3DDEVICE9 pD3DDevice
	//		 const char *pFileName		ファイル名
	//		 int nPriority				プライオリティ
	// 戻値：CSceneX*
	//------------------------------
	static CSceneX *Create( LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, int nPriority = 3 );

	//------------------------------
	// ワールドマトリックス設定処理
	//------------------------------
	void SetWorld( D3DXMATRIX *pMtx ){ m_mtxWorld = *pMtx; }

  void SetLightMode(float val) { lightMode = val; }
  void SetDrawFlg(BOOL flg) { drawFlg = flg; }
  BOOL GetDrawFlg() { return drawFlg; }

protected:
	LPD3DXMESH						m_pD3DXMesh;			// メッシュ情報
	LPD3DXBUFFER					m_pD3DXBuffMat;			// マトリックス情報
	DWORD							    m_nNumMat;				// マトリックス数
	LPDIRECT3DTEXTURE9				*m_ppTex;				// テクスチャポインタのポインタ
	D3DXVECTOR3						m_vec3Scl;				// スケール
	D3DXMATRIX						m_mtxWorld;				// ワールドマトリックス
	LPDIRECT3DVERTEXDECLARATION9	m_pDeclaration;			// デクラレーションポインタ
	BOOL							m_bExistTex;			// テクスチャ有無
  LPDIRECT3DPIXELSHADER9 m_pPS;
  LPD3DXCONSTANTTABLE m_pPSC;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXSHADER9 m_pVS;
  LPD3DXCONSTANTTABLE m_pVSC;		// 定数レジスタのテーブル
  float lightMode;
  BOOL drawFlg;

  LPDIRECT3DVERTEXDECLARATION9 p_declaration_;				// デクラレーション
  LPDIRECT3DVERTEXBUFFER9 p_instancing_vertex_buffer_;
  LPDIRECT3DPIXELSHADER9 p_pixel_shader;
  LPD3DXCONSTANTTABLE p_pixel_shader_constant;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXSHADER9 p_vertex_shader;
  LPD3DXCONSTANTTABLE p_vertex_shader_constant;		// 定数レジスタのテーブル
  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
  LPDIRECT3DINDEXBUFFER9 p_index_buffer_;
  unsigned int num_vertices_;
  unsigned int num_faces_;
};

#endif
// EOF