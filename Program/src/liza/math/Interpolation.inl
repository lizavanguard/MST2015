//==============================================================================
//
// 補間関数たち [Interpolation.inl]
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
// 最小値と最大値の間を線形補間するよ
//------------------------------------------------
template<typename T>
inline T InterpolateLinear( const float t, const T& A, const T& B ) {
	return T( A * ( 1 - t ) + B * t );
}


//------------------------------------------------
// 二次補間(ease-in?)
// 下に凸
// 緩やかにスタートする
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseIn( const float t, const T& A, const T& B ) {
	const float vt = t * t;
	return T( A * ( 1 - vt ) + B * vt ); 
}


//------------------------------------------------
// 二次補間(ease-out?)
// 上に凸
// 緩やかにエンドする
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseOut( const float t, const T& A, const T& B ) {
	const float vt = t * ( 2 - t );
	return T( A * ( 1 - vt ) + B * vt );
}


//------------------------------------------------
// 三次補間(ease-in, ease-out?)
// ぐねぐね曲がるやつ
// 緩やかにスタートし緩やかにエンドする
//------------------------------------------------
template<typename T>
inline T InterpolateCubic( float t, const T& A, const T& B ) {
	const float vt = t * t * ( 3 - ( 2 * t ) );
	return T( A * ( 1 - vt ) + B * vt );
}


//------------------------------------------------
// 三角関数補間(ease-in, ease-out?)
// ぐねぐね曲がるやつ
// 三次関数補間より負荷が高くて意味なし
//------------------------------------------------
template<typename T>
inline T InterpolateTrigonometric( float t, const T& A, const T& B ) {
	const float vt = ( 1 - cos( t * kPIf ) ) * 0.5f;
	return T( A * ( 1 - vt ) + B * vt );
}


#endif // __INL_LIZAMATHINTERPOLATION_INL__