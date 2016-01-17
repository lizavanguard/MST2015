//=============================================================================
//
// �Q�[���t�F�C�Y�����w�b�_�[ [CGame.h]
// Author : �@�� ��
//
//=============================================================================
#pragma once
#ifndef _CGAME_H_
#define _CGAME_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CFade;
class CPause;
class CSceneX;

const int kPallNum = 10;

//------------------------------
// �Q�[���t�F�C�Y�N���X
//------------------------------
class CGame {
public:
	//------------------------------
	// �R���X�g���N�^
	//------------------------------
	CGame();

	//------------------------------
	// �f�X�g���N�^
	//------------------------------
	~CGame(){}

	//------------------------------
	// �Q�[���t�F�C�Y����������
	// �����FLPDIRECT3DDEVICE9 pDevice
	// �ߒl�FHRESULT ����
	//------------------------------
	HRESULT Init( LPDIRECT3DDEVICE9 pDevice );

	//------------------------------
	// �Q�[���t�F�C�Y�I������
	//------------------------------
	void Uninit();

	//------------------------------
	// �Q�[���t�F�C�Y�X�V����
	//------------------------------
  void Update();

  void Draw() {}

private:
	CFade		*m_pFade;			// �t�F�C�h�N���X�|�C���^
	CPause		*m_pPause;			// �|�[�Y�N���X�|�C���^
  CSceneX *m_pX[2];
  btDynamicsWorld* btDynamicsWorld;   // Bullet�̃��[���h
  btRigidBody* btGroundBody;  // �n��
  btRigidBody* btFallBody;    // �������镨��
  btRigidBody* btPallBody[kPallNum]; // ��
  int bulletSimulateStep;
};

#endif
// EOF