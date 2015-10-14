//==============================================================================
//
// DirectX用のウィンドウ管理クラス [DirectXWindow.h]
// Created : Shimizu Shoji
//
// do_update とかに値を入れてupdateの中身も考える
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