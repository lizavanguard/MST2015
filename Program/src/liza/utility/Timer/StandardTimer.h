//==============================================================================
//
// �W���I�ȃ^�C�}�[ [StandardTimer.h]
// Created : Shimizu Shoji
// MEMO:
//  �J�E���g�A�b�v�̏ꍇ�͂Ђ����疳���ɃJ�E���g�A�b�v�������� ����͂Ȃ�
//  �J�E���g�_�E���̏ꍇ���Ђ����疳���ɃJ�E���g�_�E���������� �����͂Ȃ�
//
//==============================================================================
#pragma once
#ifndef __H_LIZAUTILITYSTANDARDTIMER_H__
#define __H_LIZAUTILITYSTANDARDTIMER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <liza/utility/Timer/Timer.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

class StandardTimer : public Timer {
public:
	// ctor
	StandardTimer( float startTime = 0.0f, bool isCountUp = true ) : Timer( startTime, isCountUp ) {}

	// dtor
	virtual ~StandardTimer() {}

	// Update
	void _Update( float elapsedTime ) override {}

	// get
	bool IsEventHappened( void ) const override { return false; }
};

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYSTANDARDTIMER_H__