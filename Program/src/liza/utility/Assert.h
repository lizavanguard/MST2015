//==============================================================================
//
// Assertion Checker [Assert.h]
// Created : Shimizu Shoji
//
// MY_BREAK_ASSERT
// MY_BREAK_ASSERTMSG
// MY_BREAK_NULL_ASSERT
// MY_BREAK_MINMAX_ASSERT
// MY_BREAK_MIN_ASSERT
// MY_BREAK_MAX_ASSERT
// MY_BREAK_ALIGN4_ASSERT
// MY_BREAK_ALIGN2_ASSERT
// MY_BREAK_IF
// 使ったほうが良い
//
//==============================================================================
#ifndef __H_LIZAUTILITYASSERT_H__
#define __H_LIZAUTILITYASSERT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include <iostream>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// macro definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
//------------------------------------------------
// 通常のアサーションチェッカ
// 条件式を入力するだけ
// 出力例:
// main.cpp(17)
// 条件"handle != NULL"が成立しませんでした
//------------------------------------------------
#define MY_ASSERT( exp ) liza::utility::MyAssert( exp, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ASSERT( exp ) { if( !liza::utility::MyAssert( exp, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 任意の補足事項を追加表示するタイプ
//------------------------------------------------
#define MY_ASSERTMSG( exp, fmt ) liza::utility::MyAssertMsg( exp, fmt, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ASSERTMSG( exp, fmt ) { if( !liza::utility::MyAssertMsg( exp, fmt, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// NULLチェックを行うアサーションチェッカ
//------------------------------------------------
#define MY_NULL_ASSERT( exp ) liza::utility::MyNullAssert( (void*)exp, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_NULL_ASSERT( exp ) { if( !liza::utility::MyNullAssert( (void*)exp, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 範囲チェックを行うアサーションチェッカ
// 下限 <= x <= 上限 の範囲内ならok
//------------------------------------------------
#define MY_MINMAX_ASSERT( exp, min, max ) liza::utility::MyMinMaxAssert( exp, min, max, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MINMAX_ASSERT( exp, min, max ) { if( !liza::utility::MyMinMaxAssert( exp, min, max, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 下限チェックを行うアサーションチェッカ
// 下限 <= x ならok
//------------------------------------------------
#define MY_MIN_ASSERT( exp, min ) liza::utility::MyMinAssert( exp, min, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MIN_ASSERT( exp, min ) { if( !liza::utility::MyMinAssert( exp, min, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 上限チェックを行うアサーションチェッカ
// x <= 上限 ならok
//------------------------------------------------
#define MY_MAX_ASSERT( exp, max ) liza::utility::MyMaxAssert( exp, max, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MAX_ASSERT( exp, max ) { if( !liza::utility::MyMaxAssert( exp, max, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 4バイト境界に即したサイズであるかチェック
// sizeofで取得したサイズが4バイトの倍数ならokということ
// ex) char => 1byte なので error
//     int  => 4byte なので ok
//------------------------------------------------
#define MY_ALIGN4_ASSERT( exp ) liza::utility::MyAlign4Assert( sizeof( exp ), __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ALIGN4_ASSERT( exp ) { if( !liza::utility::MyAlign4Assert( sizeof( exp ), __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 2バイト境界に即したサイズであるかチェック
// sizeofで取得したサイズが2バイトの倍数ならokということ
// ex) char  => 1byte なので error
//     short => 2byte なので ok
//     int   => 4byte なので ok
//------------------------------------------------
#define MY_ALIGN2_ASSERT( exp ) liza::utility::MyAlign2Assert( sizeof( exp ), __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ALIGN2_ASSERT( exp ) { if( !liza::utility::MyAlign2Assert( sizeof( exp ), __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 条件式ブレイクポイント
//------------------------------------------------
#define MY_BREAK_IF( exp ) { if( ( exp ) ) { __debugbreak(); } }


#else
#define MY_ASSERT __noop
#define MY_BREAK_ASSERT __noop
#define MY_ASSERTMSG __noop
#define MY_BREAK_ASSERTMSG __noop
#define MY_NULL_ASSERT __noop
#define MY_BREAK_NULL_ASSERT __noop
#define MY_MINMAX_ASSERT __noop
#define MY_BREAK_MINMAX_ASSERT __noop
#define MY_MIN_ASSERT __noop
#define MY_BREAK_MIN_ASSERT __noop
#define MY_MAX_ASSERT __noop
#define MY_BREAK_MAX_ASSERT __noop
#define MY_ALIGN4_ASSERT __noop
#define MY_BREAK_ALIGN4_ASSERT __noop
#define MY_ALIGN2_ASSERT __noop
#define MY_BREAK_ALIGN2_ASSERT __noop
#define MY_BREAK_IF __noop
#endif


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace utility {

//------------------------------------------------
// 通常のアサーションチェッカ
//------------------------------------------------
inline bool MyAssert( bool b, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 補足事項を追加表示するタイプ
//------------------------------------------------
inline bool MyAssertMsg( bool b, const char* fmt, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// NULLチェックを行うアサーションチェッカ
//------------------------------------------------
inline bool MyNullAssert( void* p, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 範囲チェックを行うアサーションチェッカ
//------------------------------------------------
inline bool MyMinMaxAssert( int x, int min, int max, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 下限チェックを行うアサーションチェッカ
//------------------------------------------------
inline bool MyMinAssert( int x, int min, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 上限チェックを行うアサーションチェッカ
//------------------------------------------------
inline bool MyMaxAssert( int x, int max, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 4バイト境界に即した内容であるかチェック
//------------------------------------------------
inline bool MyAlign4Assert( int size, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 2バイト境界に即した内容であるかチェック
//------------------------------------------------
inline bool MyAlign2Assert( int size, const char* file, int line, const char* exp, bool doAbort = false );


// include inline-header
#include "Assert.inl"

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYASSERT_H__