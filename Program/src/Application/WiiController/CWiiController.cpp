//*****************************************************************************
//	 [ CWiiController.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "CWiiController.h"
#include <iostream>

//*****************************************************************************
//	定数定義
//*****************************************************************************

const int BUTTON_STATE_BITS[WC_BUTTON_MAX] = {
	wiimote_state::buttons::LEFT,	//	0x0001
	wiimote_state::buttons::RIGHT,	//	0x0002
	wiimote_state::buttons::DOWN,	//	0x0004
	wiimote_state::buttons::UP,		//	0x0008
	wiimote_state::buttons::PLUS,	//	0x0010
	wiimote_state::buttons::TWO,	//	0x0100
	wiimote_state::buttons::ONE,	//	0x0200
	wiimote_state::buttons::_B,		//	0x0400
	wiimote_state::buttons::_A,		//	0x0800
	wiimote_state::buttons::MINUS,	//	0x1000
	wiimote_state::buttons::HOME	//	0x8000
};

//=============================================================================
//	コンストラクタ
//=============================================================================
CWiiController::CWiiController() :
connectFlag(false),
accel(),
accelPrev(),
rot(),
rotPrev()
{
	//	本体を生成
	wiiRemote = new wiimote();

	//	試行回数
	int connectTryCount = 0;
	std::cerr << "waiting connection... \t";

	//	コントローラの本体が、接続できるまでループ
	while (!wiiRemote->Connect())
	{
		Sleep(10);

		if (connectTryCount >= CONNECT_TRY_NUM)
		{
			//	エラー値格納
			connectTryCount = -1;
			//MESSAGE("wiiリモコンの接続はされませんでした");

      //MY_BREAK_ASSERT(false);
			return;
		}
		connectTryCount++;
	}

	// 使用するセンサを設定（ボタン、加速度、IR、エクステンション）
	wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);

	// LEDをプレイヤーNoに合わせて点灯させるよ
	wiiRemote->SetLEDs(1);

	//	スピーカーを有効にする
	wiiRemote->MuteSpeaker(false);
	wiiRemote->EnableSpeaker(true);

	//	接続状態へ移行
	connectFlag = true;

	std::cerr << "connection success" << std::endl;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CWiiController::~CWiiController()
{
	//	切断
	wiiRemote->Disconnect();

	SafeDelete(wiiRemote);
}

//=============================================================================
//	更新処理
//=============================================================================
void CWiiController::update()
{
	//	前回の状態を保存
	buttonStatePrev = buttonState;
	accelPrev = accel;
	rotPrev = rot;

	//	wiiリモコンの状態を取得...というかリセット
	//	これやらないとステータスが更新されない
	wiiRemote->RefreshState();

	//	ボタンの押下状態を保存
	buttonState = wiiRemote->Button.Bits;

	//	加速度の状態を保存
	accel = D3DXVECTOR3(wiiRemote->Acceleration.X, wiiRemote->Acceleration.Y, wiiRemote->Acceleration.Z);
	
	//	回転角を保存
	rot = D3DXVECTOR3(wiiRemote->Acceleration.Orientation.X, wiiRemote->Acceleration.Orientation.Y, wiiRemote->Acceleration.Orientation.Z);

	//	リピートカウントの更新
	for (int count = 0; count < WC_BUTTON_MAX; count++)
	{
		if (buttonState & BUTTON_STATE_BITS[count])
		{
			(repeatCount[count] < REPEAT_COUNT_MAX) ? repeatCount[count]++ : repeatCount[count] = REPEAT_COUNT_MAX;
		}
		else
			repeatCount[count] = 0;
	}
}
//=============================================================================
//	各種ゲッター
//=============================================================================
bool CWiiController::getPress(WC_BUTTON _button)
{
	return (buttonState & BUTTON_STATE_BITS[_button]) ? true : false;
}
bool CWiiController::getTrigger(WC_BUTTON _button)
{
	return (!(buttonStatePrev & BUTTON_STATE_BITS[_button]) && (buttonState & BUTTON_STATE_BITS[_button])) ? true : false;
}
bool CWiiController::getRelease(WC_BUTTON _button)
{
	return ((buttonStatePrev & BUTTON_STATE_BITS[_button]) && !(buttonState & BUTTON_STATE_BITS[_button])) ? true : false;
}
bool CWiiController::getRepeat(WC_BUTTON _button)
{
	if (repeatCount[_button] == REPEAT_COUNT_MAX)
		return (buttonState & BUTTON_STATE_BITS[_button]) ? true : false;
	else
		return false;
}

//-----------------------------------EOF---------------------------------------