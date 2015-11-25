//==============================================================================
//
// BoundedTimer [BoundedTimer.h]
// Created : Shimizu Shoji
// MEMO:
//  境界付きのタイマー
//  リピートするかどうかを選択する
//  非リピート時は境界に達している間はフラグが立ち続ける
//  リピート時は境界を跨いだ瞬間にフラグが立ち 通常時はフラグが落ちている
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
		// if リピートする
		if( isRepeat_ ) {
			// if カウントアップなら 上限のみチェック
			if( IsCountUp() ) {
				if( time_ > upperTime_ ) {
					while( time_ > upperTime_ ) {
						time_ -= lengthTime_;
					}
					isBoundary_ = true;
				}
			}
			// else カウントダウンなら 下限のみチェック
			else {
				if( time_ < lowerTime_ ) {
					while( time_ < lowerTime_ ) {
						time_ += lengthTime_;
					}
					isBoundary_ = true;
				}
			}
		}

		// else リピートしない
		else {
			// if カウントアップなら 上限のみチェック
			if( IsCountUp() ) {
				if( time_ > upperTime_ ) {
					time_ = upperTime_;
					isBoundary_ = true;
				}
			}
			// else カウントダウンなら 下限のみチェック
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