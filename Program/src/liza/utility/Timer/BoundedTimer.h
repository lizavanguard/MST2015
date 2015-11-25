//==============================================================================
//
// BoundedTimer [BoundedTimer.h]
// Created : Shimizu Shoji
// MEMO:
//  ���E�t���̃^�C�}�[
//  ���s�[�g���邩�ǂ�����I������
//  �񃊃s�[�g���͋��E�ɒB���Ă���Ԃ̓t���O������������
//  ���s�[�g���͋��E���ׂ����u�ԂɃt���O������ �ʏ펞�̓t���O�������Ă���
//
//==============================================================================
#pragma once
#ifndef __H_LIZAUTILITYBOUNDEDTIMER_H__
#define __H_LIZAUTILITYBOUNDEDTIMER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <liza/utility/Timer/Timer.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

class BoundedTimer : public Timer {
public:
	// ctor
	BoundedTimer(
		float startTime = 0.0f,
		bool isCountUp = true,
		float lowerTime = 0.0f,
		float upperTime = 1.0f,
		bool isRepeat = false
	)
		: Timer( startTime, isCountUp )
		, lowerTime_( lowerTime )
		, upperTime_( upperTime )
		, lengthTime_( upperTime_ - lowerTime_ )
		, isRepeat_( isRepeat )
		, isBoundary_( false )
	{
		_ASSERT( lengthTime_ >= 0.0f );
	}

	// dtor
	virtual ~BoundedTimer() {}

	// Update
	void _Update( float elapsedTime ) override {
		isBoundary_ = false;
		// if ���s�[�g����
		if( isRepeat_ ) {
			// if �J�E���g�A�b�v�Ȃ� ����̂݃`�F�b�N
			if( IsCountUp() ) {
				if( time_ > upperTime_ ) {
					while( time_ > upperTime_ ) {
						time_ -= lengthTime_;
					}
					isBoundary_ = true;
				}
			}
			// else �J�E���g�_�E���Ȃ� �����̂݃`�F�b�N
			else {
				if( time_ < lowerTime_ ) {
					while( time_ < lowerTime_ ) {
						time_ += lengthTime_;
					}
					isBoundary_ = true;
				}
			}
		}

		// else ���s�[�g���Ȃ�
		else {
			// if �J�E���g�A�b�v�Ȃ� ����̂݃`�F�b�N
			if( IsCountUp() ) {
				if( time_ > upperTime_ ) {
					time_ = upperTime_;
					isBoundary_ = true;
				}
			}
			// else �J�E���g�_�E���Ȃ� �����̂݃`�F�b�N
			else {
				if( time_ < lowerTime_ ) {
					time_ = lowerTime_;
					isBoundary_ = true;
				}
			}
		}
	}

	// get
	bool IsEventHappened( void ) const override { return isBoundary_; }

private:
	// property
	float lowerTime_;
	float upperTime_;
	float lengthTime_;
	bool isRepeat_;
	bool isBoundary_;
};

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYBOUNDEDTIMER_H__