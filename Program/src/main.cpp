//==============================================================================
//
// DirectX用のウィンドウ管理クラス [DirectXWindow.h]
// Created : Shimizu Shoji
//
// Fade
// Texture no Unload ??
//
// Lighting
//
// Lane(Course)
//
// 背景(cube)
// Xモデルの透明、半透明
//
// 2D(UI) シェーダ整理
// score
// 残りのピンの配置状況
// 投げた回数？
//
// ピンとwの判定しっかり(すりぬけ、ピン同士の判定、etc...)
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