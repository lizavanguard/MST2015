//==============================================================================
//
// DirectX用のウィンドウ管理クラス [DirectXWindow.h]
// Created : Shimizu Shoji
//
// ピンの吹っ飛び方を変更する
// デバッグモードで何度でも投げれるように(シーン遷移挟むのうざいから)
// ボール追従三人称カメラの追加
// シーン遷移をリモコンでも出来るようにすること
//
// カメラワークを簡単に指定できるようにする
// 一人称時にボールの見えてない方(CCW)を切る
//
// 予めモデル等を読み込んでおく
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