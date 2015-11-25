//==============================================================================
//
// ���[�e�B���e�B [Utility.inl]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAUTILITYUTILITY_INL__
#define __INL_LIZAUTILITYUTILITY_INL__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// �n���ꂽ�l�̌������Z�o���邾��
//------------------------------------------------
unsigned int liza::utility::CalcPlaceCnt( const int value ) {
	unsigned int placeCnt = 0;
	int work = value;
	do {
		work /= 10;
		++placeCnt;
	} while( work != 0 );

	return placeCnt;
}


#endif // __INL_LIZAUTILITYUTILITY_INL__