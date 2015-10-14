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
// �g�����ق����ǂ�
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
// �ʏ�̃A�T�[�V�����`�F�b�J
// ����������͂��邾��
// �o�͗�:
// main.cpp(17)
// ����"handle != NULL"���������܂���ł���
//------------------------------------------------
#define MY_ASSERT( exp ) liza::utility::MyAssert( exp, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ASSERT( exp ) { if( !liza::utility::MyAssert( exp, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// �C�ӂ̕⑫������ǉ��\������^�C�v
//------------------------------------------------
#define MY_ASSERTMSG( exp, fmt ) liza::utility::MyAssertMsg( exp, fmt, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ASSERTMSG( exp, fmt ) { if( !liza::utility::MyAssertMsg( exp, fmt, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// NULL�`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
#define MY_NULL_ASSERT( exp ) liza::utility::MyNullAssert( (void*)exp, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_NULL_ASSERT( exp ) { if( !liza::utility::MyNullAssert( (void*)exp, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// �͈̓`�F�b�N���s���A�T�[�V�����`�F�b�J
// ���� <= x <= ��� �͈͓̔��Ȃ�ok
//------------------------------------------------
#define MY_MINMAX_ASSERT( exp, min, max ) liza::utility::MyMinMaxAssert( exp, min, max, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MINMAX_ASSERT( exp, min, max ) { if( !liza::utility::MyMinMaxAssert( exp, min, max, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// �����`�F�b�N���s���A�T�[�V�����`�F�b�J
// ���� <= x �Ȃ�ok
//------------------------------------------------
#define MY_MIN_ASSERT( exp, min ) liza::utility::MyMinAssert( exp, min, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MIN_ASSERT( exp, min ) { if( !liza::utility::MyMinAssert( exp, min, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// ����`�F�b�N���s���A�T�[�V�����`�F�b�J
// x <= ��� �Ȃ�ok
//------------------------------------------------
#define MY_MAX_ASSERT( exp, max ) liza::utility::MyMaxAssert( exp, max, __FILE__, __LINE__, #exp, true )
#define MY_BREAK_MAX_ASSERT( exp, max ) { if( !liza::utility::MyMaxAssert( exp, max, __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 4�o�C�g���E�ɑ������T�C�Y�ł��邩�`�F�b�N
// sizeof�Ŏ擾�����T�C�Y��4�o�C�g�̔{���Ȃ�ok�Ƃ�������
// ex) char => 1byte �Ȃ̂� error
//     int  => 4byte �Ȃ̂� ok
//------------------------------------------------
#define MY_ALIGN4_ASSERT( exp ) liza::utility::MyAlign4Assert( sizeof( exp ), __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ALIGN4_ASSERT( exp ) { if( !liza::utility::MyAlign4Assert( sizeof( exp ), __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// 2�o�C�g���E�ɑ������T�C�Y�ł��邩�`�F�b�N
// sizeof�Ŏ擾�����T�C�Y��2�o�C�g�̔{���Ȃ�ok�Ƃ�������
// ex) char  => 1byte �Ȃ̂� error
//     short => 2byte �Ȃ̂� ok
//     int   => 4byte �Ȃ̂� ok
//------------------------------------------------
#define MY_ALIGN2_ASSERT( exp ) liza::utility::MyAlign2Assert( sizeof( exp ), __FILE__, __LINE__, #exp, true )
#define MY_BREAK_ALIGN2_ASSERT( exp ) { if( !liza::utility::MyAlign2Assert( sizeof( exp ), __FILE__, __LINE__, #exp ) ) __debugbreak(); } __noop


//------------------------------------------------
// �������u���C�N�|�C���g
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
// �ʏ�̃A�T�[�V�����`�F�b�J
//------------------------------------------------
inline bool MyAssert( bool b, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// �⑫������ǉ��\������^�C�v
//------------------------------------------------
inline bool MyAssertMsg( bool b, const char* fmt, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// NULL�`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
inline bool MyNullAssert( void* p, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// �͈̓`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
inline bool MyMinMaxAssert( int x, int min, int max, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// �����`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
inline bool MyMinAssert( int x, int min, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// ����`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
inline bool MyMaxAssert( int x, int max, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 4�o�C�g���E�ɑ��������e�ł��邩�`�F�b�N
//------------------------------------------------
inline bool MyAlign4Assert( int size, const char* file, int line, const char* exp, bool doAbort = false );


//------------------------------------------------
// 2�o�C�g���E�ɑ��������e�ł��邩�`�F�b�N
//------------------------------------------------
inline bool MyAlign2Assert( int size, const char* file, int line, const char* exp, bool doAbort = false );


// include inline-header
#include "Assert.inl"

	} // namespace utility
} // namespace liza


#endif // __H_LIZAUTILITYASSERT_H__