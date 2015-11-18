//*****************************************************************************
//	 [ CWiiController.h ]
//	Author : KOTARO NAGASAKI
//
//
//	wiiコントローラー認識用
//	wiiYourself(wiimote)のクラスを内包して、色々と使いやすくしたクラス
//
//	※注意点
//	なんか、ゲームパッドの接続をしたあとだとConnectが失敗する
//	追記	wiiリモコンを接続した状態でゲームパッドの接続を先に行うと
//			ゲームパッドとして認識されるので注意！
//*****************************************************************************
#ifndef _CWIICONTROLLER_H_
#define _CWIICONTROLLER_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "WiiYourself/wiimote.h"

//*****************************************************************************
//	定数定義
//*****************************************************************************

//	接続試行回数の上限
#define CONNECT_TRY_NUM (5)

//	ボタンの最大数
#define WC_BUTTON_MAX (11)

//	リピートカウントの最大値
#define REPEAT_COUNT_MAX (60)

//*****************************************************************************
//	列挙体定義
//*****************************************************************************

//	Wiiリモコンのボタン数
typedef enum
{
	WC_LEFT = 0,	// ←ボタン		0x0001
	WC_RIGHT,		// →ボタン		0x0002
	WC_DOWN,		// ↓ボタン		0x0004
	WC_UP,			// ↑ボタン		0x0008
	WC_PLUS,		// ＋ボタン		0x0010
	WC_TWO,			// ２ボタン		0x0100
	WC_ONE,			// １ボタン		0x0200
	WC_B,			// Ｂボタン		0x0400
	WC_A,			// Ａボタン		0x0800
	WC_MINUS,		// －ボタン		0x1000
	WC_HOME,		// HOMEボタン	0x8000
	WC_ALL,			// 総数
}WC_BUTTON;

//=============================================================================
//	クラス定義
//=============================================================================
class CWiiController
{
public:

	CWiiController();
	~CWiiController();
	void update();

	//	接続状態の取得
	bool getConnectFlag(){ return connectFlag; }

	//	各種ボタン状態の取得
	bool getPress(WC_BUTTON _button);
	bool getTrigger(WC_BUTTON _button);
	bool getRelease(WC_BUTTON _button);
	bool getRepeat(WC_BUTTON _button);

	//	加速度取得
	D3DXVECTOR3 getAcceleration(){ return accel; }
	float getAccelerationX(){ return accel.x; }
	float getAccelerationY(){ return accel.y; }
	float getAccelerationZ(){ return accel.z; }

	//	回転角取得
	D3DXVECTOR3 getRot(){ return rot; }
	float getRotX(){ return rot.x; }
	float getRotY(){ return rot.y; }
	float getRotZ(){ return rot.z; }

	//	trueで振動　falseで振動を止める
	void rumble(bool _flag){ wiiRemote->SetRumble(_flag); }
	//	指定した秒数(ミリ秒)振動させ続ける
	void rumble(unsigned int _milliseconds){ wiiRemote->RumbleForAsync(_milliseconds); }

	//	バッテリーの残量を取得
	int battery(){ return wiiRemote->BatteryPercent; }


	void reset(){ wiiRemote->Reset(); }

	//	音を出す
	//	１つ目の引数に周波数、２つ目の引数に音量（0x00 ～ 0x10）を指定
	//	停めずに終了させるとバグるから注意

	//	wiimote_common.hから抜粋した周波数
	/*enum speaker_freq
	//{
	//	FREQ_NONE = 0,
	//	FREQ_4200HZ = 1,
	//	FREQ_3920HZ = 2,
	//	FREQ_3640HZ = 3,
	//	FREQ_3360HZ = 4,
	//	FREQ_3130HZ = 5,
	//	FREQ_2940HZ = 6,
	//	FREQ_2760HZ = 7,
	//	FREQ_2610HZ = 8,
	//	FREQ_2470HZ = 9,
	};*/
	void playSound(speaker_freq _hz, BYTE _volume){ wiiRemote->PlaySquareWave(_hz, _volume); }

private:

	//	コントローラ本体
	wiimote* wiiRemote;

	//	ボタンの押下状態
	WORD buttonState;
	WORD buttonStatePrev;

	//	加速度
	D3DXVECTOR3 accel;
	D3DXVECTOR3 accelPrev;

	//	回転角
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotPrev;

	//	識別されているかどうか
	bool connectFlag;
	bool firstFlag;

	//	リピートカウントの格納
	int repeatCount[WC_ALL];
};

#endif
//-----------------------------------EOF---------------------------------------