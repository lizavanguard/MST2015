//*****************************************************************************
//	 [ CWiiController.h ]
//	Author : KOTARO NAGASAKI
//
//
//	wii�R���g���[���[�F���p
//	wiiYourself(wiimote)�̃N���X�����āA�F�X�Ǝg���₷�������N���X
//
//	�����ӓ_
//	�Ȃ񂩁A�Q�[���p�b�h�̐ڑ����������Ƃ���Connect�����s����
//	�ǋL	wii�����R����ڑ�������ԂŃQ�[���p�b�h�̐ڑ����ɍs����
//			�Q�[���p�b�h�Ƃ��ĔF�������̂Œ��ӁI
//*****************************************************************************
#ifndef _CWIICONTROLLER_H_
#define _CWIICONTROLLER_H_

//*****************************************************************************
//	�C���N���[�h��`
//*****************************************************************************
#include "WiiYourself/wiimote.h"

//*****************************************************************************
//	�萔��`
//*****************************************************************************

//	�ڑ����s�񐔂̏��
#define CONNECT_TRY_NUM (5)

//	�{�^���̍ő吔
#define WC_BUTTON_MAX (11)

//	���s�[�g�J�E���g�̍ő�l
#define REPEAT_COUNT_MAX (60)

//*****************************************************************************
//	�񋓑̒�`
//*****************************************************************************

//	Wii�����R���̃{�^����
typedef enum
{
	WC_LEFT = 0,	// ���{�^��		0x0001
	WC_RIGHT,		// ���{�^��		0x0002
	WC_DOWN,		// ���{�^��		0x0004
	WC_UP,			// ���{�^��		0x0008
	WC_PLUS,		// �{�{�^��		0x0010
	WC_TWO,			// �Q�{�^��		0x0100
	WC_ONE,			// �P�{�^��		0x0200
	WC_B,			// �a�{�^��		0x0400
	WC_A,			// �`�{�^��		0x0800
	WC_MINUS,		// �|�{�^��		0x1000
	WC_HOME,		// HOME�{�^��	0x8000
	WC_ALL,			// ����
}WC_BUTTON;

//=============================================================================
//	�N���X��`
//=============================================================================
class CWiiController
{
public:

	CWiiController();
	~CWiiController();
	void update();

	//	�ڑ���Ԃ̎擾
	bool getConnectFlag(){ return connectFlag; }

	//	�e��{�^����Ԃ̎擾
	bool getPress(WC_BUTTON _button);
	bool getTrigger(WC_BUTTON _button);
	bool getRelease(WC_BUTTON _button);
	bool getRepeat(WC_BUTTON _button);

	//	�����x�擾
	D3DXVECTOR3 getAcceleration(){ return accel; }
	float getAccelerationX(){ return accel.x; }
	float getAccelerationY(){ return accel.y; }
	float getAccelerationZ(){ return accel.z; }

	//	��]�p�擾
	D3DXVECTOR3 getRot(){ return rot; }
	float getRotX(){ return rot.x; }
	float getRotY(){ return rot.y; }
	float getRotZ(){ return rot.z; }

	//	true�ŐU���@false�ŐU�����~�߂�
	void rumble(bool _flag){ wiiRemote->SetRumble(_flag); }
	//	�w�肵���b��(�~���b)�U������������
	void rumble(unsigned int _milliseconds){ wiiRemote->RumbleForAsync(_milliseconds); }

	//	�o�b�e���[�̎c�ʂ��擾
	int battery(){ return wiiRemote->BatteryPercent; }


	void reset(){ wiiRemote->Reset(); }

	//	�����o��
	//	�P�ڂ̈����Ɏ��g���A�Q�ڂ̈����ɉ��ʁi0x00 �` 0x10�j���w��
	//	��߂��ɏI��������ƃo�O�邩�璍��

	//	wiimote_common.h���甲���������g��
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

	//	�R���g���[���{��
	wiimote* wiiRemote;

	//	�{�^���̉������
	WORD buttonState;
	WORD buttonStatePrev;

	//	�����x
	D3DXVECTOR3 accel;
	D3DXVECTOR3 accelPrev;

	//	��]�p
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotPrev;

	//	���ʂ���Ă��邩�ǂ���
	bool connectFlag;
	bool firstFlag;

	//	���s�[�g�J�E���g�̊i�[
	int repeatCount[WC_ALL];
};

#endif
//-----------------------------------EOF---------------------------------------