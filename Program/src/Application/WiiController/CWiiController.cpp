//*****************************************************************************
//	 [ CWiiController.cpp ]
//	Author : KOTARO NAGASAKI
//*****************************************************************************

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "CWiiController.h"
#include <iostream>

//*****************************************************************************
//	�萔��`
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
//	�R���X�g���N�^
//=============================================================================
CWiiController::CWiiController() :
connectFlag(false),
accel(),
accelPrev(),
rot(),
rotPrev()
{
	//	�{�̂𐶐�
	wiiRemote = new wiimote();

	//	���s��
	int connectTryCount = 0;
	std::cerr << "waiting connection... \t";

	//	�R���g���[���̖{�̂��A�ڑ��ł���܂Ń��[�v
	while (!wiiRemote->Connect())
	{
		Sleep(10);

		if (connectTryCount >= CONNECT_TRY_NUM)
		{
			//	�G���[�l�i�[
			connectTryCount = -1;
			//MESSAGE("wii�����R���̐ڑ��͂���܂���ł���");

      //MY_BREAK_ASSERT(false);
			return;
		}
		connectTryCount++;
	}

	// �g�p����Z���T��ݒ�i�{�^���A�����x�AIR�A�G�N�X�e���V�����j
	wiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);

	// LED���v���C���[No�ɍ��킹�ē_���������
	wiiRemote->SetLEDs(1);

	//	�X�s�[�J�[��L���ɂ���
	wiiRemote->MuteSpeaker(false);
	wiiRemote->EnableSpeaker(true);

	//	�ڑ���Ԃֈڍs
	connectFlag = true;

	std::cerr << "connection success" << std::endl;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CWiiController::~CWiiController()
{
	//	�ؒf
	wiiRemote->Disconnect();

	SafeDelete(wiiRemote);
}

//=============================================================================
//	�X�V����
//=============================================================================
void CWiiController::update()
{
	//	�O��̏�Ԃ�ۑ�
	buttonStatePrev = buttonState;
	accelPrev = accel;
	rotPrev = rot;

	//	wii�����R���̏�Ԃ��擾...�Ƃ��������Z�b�g
	//	������Ȃ��ƃX�e�[�^�X���X�V����Ȃ�
	wiiRemote->RefreshState();

	//	�{�^���̉�����Ԃ�ۑ�
	buttonState = wiiRemote->Button.Bits;

	//	�����x�̏�Ԃ�ۑ�
	accel = D3DXVECTOR3(wiiRemote->Acceleration.X, wiiRemote->Acceleration.Y, wiiRemote->Acceleration.Z);
	
	//	��]�p��ۑ�
	rot = D3DXVECTOR3(wiiRemote->Acceleration.Orientation.X, wiiRemote->Acceleration.Orientation.Y, wiiRemote->Acceleration.Orientation.Z);

	//	���s�[�g�J�E���g�̍X�V
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
//	�e��Q�b�^�[
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