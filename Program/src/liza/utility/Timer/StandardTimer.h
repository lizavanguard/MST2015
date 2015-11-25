//==============================================================================
//
// 標準的なタイマー [StandardTimer.h]
// Created : Shimizu Shoji
// MEMO:
//  カウントアップの場合はひたすら無限にカウントアップし続ける 上限はない
//  カウントダウンの場合もひたすら無限にカウントダウンし続ける 下限はない
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