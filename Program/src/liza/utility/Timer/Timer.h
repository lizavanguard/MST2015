//==============================================================================
//
// Timer [Timer.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAUTILITYTIMER_H__
#define __H_LIZAUTILITYTIMER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

class Timer {
public:
	// ctor
	Timer( float startTime, bool isCountUp )
		: time_( startTime )
		, sign_( isCountUp ? 1 : -1 )
		, isStarting_( true )
	{
	}

	// dtor
	virtual ~Timer() {}

	// Update
	void Update( float elapsedTime ) {
		// if “®‚¢‚Ä‚¢‚é‚È‚ç
		if( isStarting_ ) {
			// ŽžŠÔ‚Ì‰ÁŽZ
			time_ += ( elapsedTime * sign_ );

			// ”h¶ƒNƒ‰ƒX‚ÅŽÀ‘•
			_Update( elapsedTime );
		}
	}

	// Start timer
	void Start( void ) { isStarting_ = true; }
	// Stop timer
	void Stop( void ) { isStarting_ = false; }

	// get
	unsigned int GetFormattedMinute( void ) const { return ( abs( int( time_ ) ) / 60 ); }
	unsigned int GetFormattedSecond( void ) const { return ( abs( int( time_ ) ) % 60 ); }
	unsigned int GetFormattedMSecond( void ) const { return (unsigned int)( abs( ( time_ - int( time_ ) ) ) * 100 ); }
	unsigned int GetSecond( void ) const { return abs( int( time_ ) ); }
	float GetRawTime( void ) const { return time_; }
	bool IsPositive( void ) const { return time_ > 0.0f; }
	bool IsCountUp( void ) const { return sign_ == 1; }
	bool IsStarting( void ) const { return isStarting_; }

	// ‰½‚©‚ÉŽg‚Á‚Ä
	virtual bool IsEventHappened( void ) const = 0;

	// set
	void SetRawTime( float time ) { time_ = time; }
	void OnCountUp( void ) { sign_ = 1; }
	void OnCountDown( void ) { sign_ = -1; }

protected:
	// Update impl
	virtual void _Update( float elapsedTime ) = 0;

	// property
	float time_;
	int sign_;
	bool isStarting_;
};

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYTIMER_H__