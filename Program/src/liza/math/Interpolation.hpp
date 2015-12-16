//==============================================================================
//
// 補間関数たち [Interpolation.hpp]
// Created : Shimizu Shoji
// MEMO:
//  戻値をオブジェクトにしているよ
//  また、実装の話に少し入るけどもreturn文で直接テンポラリオブジェクトの構築をしているよ
//  こうすることで、コンパイラが戻値を最適化してくれる確率が高まるよ
//  そうなれば、関数内部のテンポラリオブジェクトと、戻値におけるテンポラリオブジェクトが消えるよ
//  不思議だね
//  また、inlineにしておけば関数呼び出し自体のコストもなくなってバンバンザイだね
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
// 最小値と最大値の間を線形補間するよ
//------------------------------------------------
template<typename T>
inline T InterpolateLinear( float t, const T& A, const T& B );


//------------------------------------------------
// 二次補間(ease-in?)
// 下に凸
// 緩やかにスタートする
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseIn( float t, const T& A, const T& B );


//------------------------------------------------
// 二次補間(ease-out?)
// 上に凸
// 緩やかにエンドする
//------------------------------------------------
template<typename T>
inline T InterpolateQuadraticEaseOut( float t, const T& A, const T& B );


//------------------------------------------------
// 三次補間(ease-in, ease-out?)
// ぐねぐね曲がるやつ
// 緩やかにスタートし緩やかにエンドする
//------------------------------------------------
template<typename T>
inline T InterpolateCubic( float t, const T& A, const T& B );

//------------------------------------------------
// 三角関数補間(ease-in, ease-out?)
// ぐねぐね曲がるやつ
// 三次関数補間より負荷が高くて意味なし
//------------------------------------------------
template<typename T>
inline T InterpolateTrigonometric( float t, const T& A, const T& B );


// inline
#include "Interpolation.inl"

	} // namespace math
} // namespace liza


#endif // __HPP_LIZAMATHINTERPOLATION_HPP__