//==============================================================================
//
// ��Ԋ֐����� [Interpolation.hpp]
// Created : Shimizu Shoji
// MEMO:
//  �ߒl���I�u�W�F�N�g�ɂ��Ă����
//  �܂��A�����̘b�ɏ������邯�ǂ�return���Œ��ڃe���|�����I�u�W�F�N�g�̍\�z�����Ă����
//  �������邱�ƂŁA�R���p�C�����ߒl���œK�����Ă����m�������܂��
//  �����Ȃ�΁A�֐������̃e���|�����I�u�W�F�N�g�ƁA�ߒl�ɂ�����e���|�����I�u�W�F�N�g���������
//  �s�v�c����
//  �܂��Ainline�ɂ��Ă����Ί֐��Ăяo�����̂̃R�X�g���Ȃ��Ȃ��ăo���o���U�C����
//
//==============================================================================
#pragma once
#ifndef __HPP_LIZAMATHINTERPOLATION_HPP__
#define __HPP_LIZAMATHINTERPOLATION_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <math.h>
#include "MathConst.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace math {

//------------------------------------------------
// �ŏ��l�ƍő�l�̊Ԃ���`��Ԃ����
//------------------------------------------------
template<typename T>
inline T InterpolateLinear( float t, const T& A, const T& B );


//------------------------------------------------
// �񎟕��(ease-in?)
// ���ɓ�
// �ɂ₩�ɃX�^�[�g����
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseIn( float t, const T& A, const T& B );


//------------------------------------------------
// �񎟕��(ease-out?)
// ��ɓ�
// �ɂ₩�ɃG���h����
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseOut( float t, const T& A, const T& B );


//------------------------------------------------
// �O�����(ease-in, ease-out?)
// ���˂��ˋȂ�����
// �ɂ₩�ɃX�^�[�g���ɂ₩�ɃG���h����
//------------------------------------------------
template<typename T>
inline T InterpolateCubic( float t, const T& A, const T& B );

//------------------------------------------------
// �O�p�֐����(ease-in, ease-out?)
// ���˂��ˋȂ�����
// �O���֐���Ԃ�蕉�ׂ������ĈӖ��Ȃ�
//------------------------------------------------
template<typename T>
inline T InterpolateTrigonometric( float t, const T& A, const T& B );


// inline
#include "Interpolation.inl"

	} // namespace math
} // namespace liza


#endif // __HPP_LIZAMATHINTERPOLATION_HPP__