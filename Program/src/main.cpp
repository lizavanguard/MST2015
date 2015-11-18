//==============================================================================
//
// DirectX�p�̃E�B���h�E�Ǘ��N���X [DirectXWindow.h]
// Created : Shimizu Shoji
//
// Fade
// Texture no Unload ??
//
// Lighting
//
// Lane(Course)
//
// �w�i(cube)
// X���f���̓����A������
//
// 2D(UI) �V�F�[�_����
// score
// �c��̃s���̔z�u��
// �������񐔁H
//
// �s����w�̔��肵������(����ʂ��A�s�����m�̔���Aetc...)
//
// MEMO:
//  [�����_�����O�p�C�v���C��]
//    1. �w�肵�������̃����_�[�^�[�Q�b�g�ɕ`��
//    2. �|�X�g�G�t�F�N�g��������(�\��)
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "liza/utility/HandyLeakCheck.h"

#include "Framework/GameWindow/GameWindow.h"
#include "Framework/GameWindow/GameDirectX.h"

#include "window_config.h"

//==============================================================================
// EntryPoint
//==============================================================================
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow ) {
	liza::utility::BeginLeakCheck();

	GameWindow gameWindow(
		hInstance,
		nCmdShow,
		kWindowName,
		kWindowWidth,
		kWindowHeight,
		new GameDirectX()
	);

	gameWindow.Run();

	return 0;
}