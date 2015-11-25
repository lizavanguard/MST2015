//==============================================================================
//
// Counter [Counter.h]
// Created : Shimizu Shoji
// MEMO:
//  初期値と桁数を指定
//  桁数を超えないようになる シンプル
//  ex) 2桁
//  0-99
//  ex) 5桁
//  0-99999
//
//==============================================================================
#pragma once
#ifndef __H_LIZAUTILITYCOUNTER_H__
#define __H_LIZAUTILITYCOUNTER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

class Counter {
public:
	// ctor
	Counter( unsigned int value, unsigned int placeMax )
		: placeMax_( placeMax )
		, value_( value )
		, valueMax_( 0 )
	{
		_CalcValueMax();
		_Clamp();
	}

	// Add
	void AddValue( unsigned int value ) {
		value_ += value;
		_Clamp();
	}

	// Change max place
	void ChangePlaceMax( unsigned int placeMax ) {
		placeMax_ = placeMax;
		_CalcValueMax();
		_Clamp();
	}

	// Dec
	void DecValue( unsigned int value ) {
		int temp = value_ - value;
		if( temp < 0 ) {
			temp = 0;
		}
		value_ = temp;
	}

	// get
	unsigned int GetPlaceMax( void ) const { return placeMax_; }
	unsigned int GetValue( void ) const { return value_; }
	unsigned int GetValueMax( void ) const { return valueMax_; }
	
	// set
	void SetValue( unsigned int value ) {
		value_ = value;
		_Clamp();
	}

private:
	// Calculate max value
	void _CalcValueMax( void ) {
		// (10^桁数)-1
		valueMax_ = (unsigned int)( powf( 10.0f, (float)placeMax_ ) ) - 1;
	}

	// Clamp value
	void _Clamp( void ) {
		if( value_ > valueMax_ ) {
			value_ = valueMax_;
		}
	}

	// property
	unsigned int placeMax_;
	unsigned int value_;
	unsigned int valueMax_;
};

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYCOUNTER_H__