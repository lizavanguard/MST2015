//==============================================================================
//
// Assertion Checker [MyAssert.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAUTILITYASSERT_INL__
#define __INL_LIZAUTILITYASSERT_INL__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Assert.h"


//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// 通常のアサーションチェッカ
//------------------------------------------------
bool MyAssert( const bool b, const char* const file, const int line, const char* const exp, const bool doAbort ) {
#ifdef _DEBUG
	// if 条件が偽なら
	if( !b ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: \" " << exp << " \" が成立しませんでした" << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 補足事項を追加表示するタイプ
//------------------------------------------------
bool MyAssertMsg(
	const bool b,
	const char* const fmt,
	const char* const file,
	const int line,
	const char* const exp,
	const bool doAbort
) {
#ifdef _DEBUG
	// if 条件が偽なら
	if( !b ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー:\" " << exp << " \" が成立しませんでした" << std::endl;
		std::cerr << "補足事項: " << fmt << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// NULLチェックを行うアサーションチェッカ
//------------------------------------------------
bool MyNullAssert( void* const p, const char* const file, const int line, const char* const exp, const bool doAbort ) {
#ifdef _DEBUG
	// if ポインタがNULLなら
	if( p == NULL ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: " << exp << " がNULLで使用されています" << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 範囲チェックを行うアサーションチェッカ
//------------------------------------------------
bool MyMinMaxAssert(
	const int x,
	const int min,
	const int max,
	const char* const file,
	const int line,
	const char* const exp,
	const bool doAbort
) {
#ifdef _DEBUG
	(void)exp;
	// min と max がそもそも正しいかチェック
	// if min の方が大きいなら
	if( min > max ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: MY_MINMAX_ASSERTの引数 min, max に不正な値が渡されています" << std::endl
			<< "      : min が max より大きい値になっています" << std::endl
			<< "      : min = " << min << ", max = " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}

	// x が範囲外かチェック
	if( ( x < min ) || ( max < x ) ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: \" " << min << " <= x <= " << max << " \" が成立しませんでした" << std::endl
			<< "      : \" " << min << " <= " << x << " <= " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 下限チェックを行うアサーションチェッカ
//------------------------------------------------
bool MyMinAssert(
	const int x,
	const int min,
	const char* const file,
	const int line,
	const char* const exp,
	const bool doAbort
) {
#ifdef _DEBUG
	(void)exp;
	// x が範囲外かチェック
	if( x < min ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: \" " << min << " <= x \" が成立しませんでした" << std::endl
			<< "      : \" " << min << " <= " << x << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 上限チェックを行うアサーションチェッカ
//------------------------------------------------
bool MyMaxAssert(
	const int x,
	const int max,
	const char* const file,
	const int line,
	const char* const exp,
	const bool doAbort
) {
#ifdef _DEBUG
	(void)exp;
	// x が範囲外かチェック
	if( max < x ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: \" x <= " << max << "が成立しませんでした" << std::endl
			<< "      : \" " << x << " <= " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 4バイト境界に即した内容であるかチェック
//------------------------------------------------
bool MyAlign4Assert( int size, const char* file, int line, const char* exp, const bool doAbort ) {
#ifdef _DEBUG
	(void)exp;
	// x が4バイト境界かチェック
	if( ( size % 4 ) != 0 ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: x が 4バイトのアラインメント境界上にありません" << std::endl
			<< "      : x のサイズ = " << size << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 2バイト境界に即した内容であるかチェック
//------------------------------------------------
bool MyAlign2Assert( int size, const char* file, int line, const char* exp, const bool doAbort ) {
#ifdef _DEBUG
	(void)exp;
	// x が2バイト境界かチェック
	if( ( size % 2 ) != 0 ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "エラー: x が 2バイトのアラインメント境界上にありません " << std::endl
			<< "      : x のサイズ = " << size << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


#endif // __INL_LIZAUTILITYASSERT_INL__