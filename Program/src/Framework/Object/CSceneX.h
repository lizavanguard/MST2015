//=============================================================================
//
// �V�[���w���f�������w�b�_�[ [CSceneX.h]
// Author : �@�� ��
//
//=============================================================================
#pragma once
#ifndef _CSCENEX_H_
#define _CSCENEX_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "CVertexBuffer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//------------------------------
// �V�[���w���f���N���X
//------------------------------
class CSceneX
{

public:
	//------------------------------
	// �R���X�g���N�^
	// �����FLPDIRECT3DDEVICE9 pD3DDevice
	//		 const char *pFileName		�t�@�C����
	//		 OBJTYPE objType			�I�u�W�F�N�g�^�C�v
	//		 int nPriority				�v���C�I���e�B
	//------------------------------
	CSceneX( LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, OBJTYPE objType = OBJTYPE_X, int nPriority = 3 );

	//------------------------------
	// �f�X�g���N�^
	//------------------------------
	~CSceneX();

	//------------------------------
	// ����������
	//------------------------------
	HRESULT Init( void );

	//------------------------------
	// �I������
	//------------------------------
	void Uninit( void );

	//------------------------------
	// �X�V����
	//------------------------------
	void Update( void );

	//------------------------------
	// �`�揈��
	//------------------------------
	void Draw( void );

	//------------------------------
	// ���W�ݒ菈��
	//------------------------------
	void SetPos( float x, float y, float z );
	void SetPos( D3DXVECTOR3 pos );

	//------------------------------
	// ���W�擾����
	//------------------------------
	D3DXVECTOR3 GetPos( void );

	//------------------------------
	// ��]�ݒ菈��
	//------------------------------
	void SetRot( float x, float y, float z );
	void SetRot( D3DXVECTOR3 rot );

	//------------------------------
	// ��]�擾����
	//------------------------------
	D3DXVECTOR3 GetRot( void );

	//------------------------------
	// �e�N�X�`���ݒ菈��
	//------------------------------
	void SetTexture( CTexture::TEXTURE_TYPE type );

	//------------------------------
	// CSceneX��������
	// �����FLPDIRECT3DDEVICE9 pD3DDevice
	//		 const char *pFileName		�t�@�C����
	//		 int nPriority				�v���C�I���e�B
	// �ߒl�FCSceneX*
	//------------------------------
	static CSceneX *Create( LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, int nPriority = 3 );

	//------------------------------
	// ���[���h�}�g���b�N�X�ݒ菈��
	//------------------------------
	void SetWorld( D3DXMATRIX *pMtx ){ m_mtxWorld = *pMtx; }

  void SetLightMode(float val) { lightMode = val; }
  void SetDrawFlg(BOOL flg) { drawFlg = flg; }
  BOOL GetDrawFlg() { return drawFlg; }

protected:
	LPD3DXMESH						m_pD3DXMesh;			// ���b�V�����
	LPD3DXBUFFER					m_pD3DXBuffMat;			// �}�g���b�N�X���
	DWORD							    m_nNumMat;				// �}�g���b�N�X��
	LPDIRECT3DTEXTURE9				*m_ppTex;				// �e�N�X�`���|�C���^�̃|�C���^
	D3DXVECTOR3						m_vec3Scl;				// �X�P�[��
	D3DXMATRIX						m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXDECLARATION9	m_pDeclaration;			// �f�N�����[�V�����|�C���^
	BOOL							m_bExistTex;			// �e�N�X�`���L��
  LPDIRECT3DPIXELSHADER9 m_pPS;
  LPD3DXCONSTANTTABLE m_pPSC;		// �萔���W�X�^�̃e�[�u��
  LPDIRECT3DVERTEXSHADER9 m_pVS;
  LPD3DXCONSTANTTABLE m_pVSC;		// �萔���W�X�^�̃e�[�u��
  float lightMode;
  BOOL drawFlg;

  LPDIRECT3DVERTEXDECLARATION9 p_declaration_;				// �f�N�����[�V����
  LPDIRECT3DVERTEXBUFFER9 p_instancing_vertex_buffer_;
  LPDIRECT3DPIXELSHADER9 p_pixel_shader;
  LPD3DXCONSTANTTABLE p_pixel_shader_constant;		// �萔���W�X�^�̃e�[�u��
  LPDIRECT3DVERTEXSHADER9 p_vertex_shader;
  LPD3DXCONSTANTTABLE p_vertex_shader_constant;		// �萔���W�X�^�̃e�[�u��
  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
  LPDIRECT3DINDEXBUFFER9 p_index_buffer_;
  unsigned int num_vertices_;
  unsigned int num_faces_;
};

#endif
// EOF