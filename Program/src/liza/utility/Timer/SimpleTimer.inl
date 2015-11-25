//==============================================================================
//
// SimpleTimer
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SimpleTimer.h"

#include <Windows.h>

#pragma comment ( lib, "winmm.lib" )

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
// �^�C�}�[�̒ʒm�Ԋu��ݒ肷��
//------------------------------------------------
liza::utility::SimpleTimer::SimpleTimer() : start_time_(0.0f) {
  Reset();
}

//------------------------------------------------
// Update
// �o�ߎ��Ԃ��X�V
//------------------------------------------------
float liza::utility::SimpleTimer::Update(void) {
  return _GetTime() -start_time_;
}

//------------------------------------------------
// Reset
//------------------------------------------------
void liza::utility::SimpleTimer::Reset(void) {
  start_time_ = _GetTime();
}

//------------------------------------------------
// ���Ԃ�Ԃ�
//------------------------------------------------
float liza::utility::SimpleTimer::_GetTime(void) const {
  return static_cast<float>(timeGetTime());
}