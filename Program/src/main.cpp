//==============================================================================
//
// DirectX�p�̃E�B���h�E�Ǘ��N���X [DirectXWindow.h]
// Created : Shimizu Shoji
//
// �s���̐�����ѕ���ύX����
// �f�o�b�O���[�h�ŉ��x�ł��������悤��(�V�[���J�ڋ��ނ̂���������)
// �{�[���Ǐ]�O�l�̃J�����̒ǉ�
//
// �J�������[�N���ȒP�Ɏw��ł���悤�ɂ���
// ��l�̎��Ƀ{�[���̌����ĂȂ���(CCW)��؂�
//
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