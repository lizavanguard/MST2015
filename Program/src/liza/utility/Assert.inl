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
// �ʏ�̃A�T�[�V�����`�F�b�J
//------------------------------------------------
bool MyAssert( const bool b, const char* const file, const int line, const char* const exp, const bool doAbort ) {
#ifdef _DEBUG
	// if �������U�Ȃ�
	if( !b ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: \" " << exp << " \" ���������܂���ł���" << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// �⑫������ǉ��\������^�C�v
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
	// if �������U�Ȃ�
	if( !b ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[:\" " << exp << " \" ���������܂���ł���" << std::endl;
		std::cerr << "�⑫����: " << fmt << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// NULL�`�F�b�N���s���A�T�[�V�����`�F�b�J
//------------------------------------------------
bool MyNullAssert( void* const p, const char* const file, const int line, const char* const exp, const bool doAbort ) {
#ifdef _DEBUG
	// if �|�C���^��NULL�Ȃ�
	if( p == NULL ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: " << exp << " ��NULL�Ŏg�p����Ă��܂�" << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// �͈̓`�F�b�N���s���A�T�[�V�����`�F�b�J
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
	// min �� max �������������������`�F�b�N
	// if min �̕����傫���Ȃ�
	if( min > max ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: MY_MINMAX_ASSERT�̈��� min, max �ɕs���Ȓl���n����Ă��܂�" << std::endl
			<< "      : min �� max ���傫���l�ɂȂ��Ă��܂�" << std::endl
			<< "      : min = " << min << ", max = " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}

	// x ���͈͊O���`�F�b�N
	if( ( x < min ) || ( max < x ) ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: \" " << min << " <= x <= " << max << " \" ���������܂���ł���" << std::endl
			<< "      : \" " << min << " <= " << x << " <= " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// �����`�F�b�N���s���A�T�[�V�����`�F�b�J
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
	// x ���͈͊O���`�F�b�N
	if( x < min ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: \" " << min << " <= x \" ���������܂���ł���" << std::endl
			<< "      : \" " << min << " <= " << x << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// ����`�F�b�N���s���A�T�[�V�����`�F�b�J
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
	// x ���͈͊O���`�F�b�N
	if( max < x ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: \" x <= " << max << "���������܂���ł���" << std::endl
			<< "      : \" " << x << " <= " << max << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 4�o�C�g���E�ɑ��������e�ł��邩�`�F�b�N
//------------------------------------------------
bool MyAlign4Assert( int size, const char* file, int line, const char* exp, const bool doAbort ) {
#ifdef _DEBUG
	(void)exp;
	// x ��4�o�C�g���E���`�F�b�N
	if( ( size % 4 ) != 0 ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: x �� 4�o�C�g�̃A���C�������g���E��ɂ���܂���" << std::endl
			<< "      : x �̃T�C�Y = " << size << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


//------------------------------------------------
// 2�o�C�g���E�ɑ��������e�ł��邩�`�F�b�N
//------------------------------------------------
bool MyAlign2Assert( int size, const char* file, int line, const char* exp, const bool doAbort ) {
#ifdef _DEBUG
	(void)exp;
	// x ��2�o�C�g���E���`�F�b�N
	if( ( size % 2 ) != 0 ) {
		std::cerr << std::endl << file << " (" << line << "):" << std::endl
			<< "�G���[: x �� 2�o�C�g�̃A���C�������g���E��ɂ���܂��� " << std::endl
			<< "      : x �̃T�C�Y = " << size << std::endl;

		doAbort ? abort() : __noop;
		return false;
	}
#endif
	return true;
}


#endif // __INL_LIZAUTILITYASSERT_INL__