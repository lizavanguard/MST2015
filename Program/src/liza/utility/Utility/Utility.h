//==============================================================================
//
// ユーティリティ [Utility.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAUTILITYUTILITY_H__
#define __H_LIZAUTILITYUTILITY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

//------------------------------------------------
// 渡された値の桁数を算出するだけ
//------------------------------------------------
inline unsigned int CalcPlaceCnt( int value );

	} // namespace utility
} // namespace liza

#include "Utility.inl"


#endif // __H_LIZAUTILITYUTILITY_H__