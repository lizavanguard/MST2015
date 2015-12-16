//==============================================================================
//
// ��Ԋ֐����� [Interpolation.inl]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAMATHINTERPOLATION_INL__
#define __INL_LIZAMATHINTERPOLATION_INL__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// �ŏ��l�ƍő�l�̊Ԃ���`��Ԃ����
//------------------------------------------------
template<typename T>
inline T InterpolateLinear( const float t, const T& A, const T& B ) {
	return T( A * ( 1 - t ) + B * t );
}


//------------------------------------------------
// �񎟕��(ease-in?)
// ���ɓ�
// �ɂ₩�ɃX�^�[�g����
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseIn( const float t, const T& A, const T& B ) {
	const float vt = t * t;
	return T( A * ( 1 - vt ) + B * vt ); 
}


//------------------------------------------------
// �񎟕��(ease-out?)
// ��ɓ�
// �ɂ₩�ɃG���h����
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseOut( const float t, const T& A, const T& B ) {
	const float vt = t * ( 2 - t );
	return T( A * ( 1 - vt ) + B * vt );
}


//------------------------------------------------
// �O�����(ease-in, ease-out?)
// ���˂��ˋȂ�����
// �ɂ₩�ɃX�^�[�g���ɂ₩�ɃG���h����
//------------------------------------------------
template<typename T>
inline T InterpolateCubic( float t, const T& A, const T& B ) {
	const float vt = t * t * ( 3 - ( 2 * t ) );
	return T( A * ( 1 - vt ) + B * vt );
}


//------------------------------------------------
// �O�p�֐����(ease-in, ease-out?)
// ���˂��ˋȂ�����
// �O���֐���Ԃ�蕉�ׂ������ĈӖ��Ȃ�
//------------------------------------------------
template<typename T>
inline T InterpolateTrigonometric( float t, const T& A, const T& B ) {
	const float vt = ( 1 - cos( t * kPIf ) ) * 0.5f;
	return T( A * ( 1 - vt ) + B * vt );
}


#endif // __INL_LIZAMATHINTERPOLATION_INL__