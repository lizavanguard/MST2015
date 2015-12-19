//==============================================================================
//
// DirectX�p�̃E�B���h�E�Ǘ��N���X [DirectXWindow.h]
// Created : Shimizu Shoji
//
// �s���̐�����ѕ���ύX����
// �f�o�b�O���[�h�ŉ��x�ł��������悤��(�V�[���J�ڋ��ނ̂���������)
// �{�[���Ǐ]�O�l�̃J�����̒ǉ�
// �V�[���J�ڂ������R���ł��o����悤�ɂ��邱��
//
// �J�������[�N���ȒP�Ɏw��ł���悤�ɂ���
// ��l�̎��Ƀ{�[���̌����ĂȂ���(CCW)��؂�
//
// �\�߃��f������ǂݍ���ł���
//
// WiiController�̊��蓖�Ă��Ă������R���g���[���[�N���X����������H
// �^�C�g���ɍs����悤�ɂ��邱�ƁA�܂���}�b�s���O
// �L���[�u�}�b�v�̉f�荞��
// ���E�ړ��ł���]
// �K�[�^�[�E�E�E�E
//
// �f�o�b�O���[�h�ŃG�t�F�N�g�Ăяo����悤��
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma warning (disable : 4204)
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