//==============================================================================
//
// DirectX用のウィンドウ管理クラス [DirectXWindow.h]
// Created : Shimizu Shoji
//
// TODO LIST:
// フェード
// カメラの切り替え
// ライト
// レーン
//
// MEMO:
//  [レンダリングパイプライン]
//    1. 指定した複数のレンダーターゲットに描画
//    2. ポストエフェクトをかける(予定)
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