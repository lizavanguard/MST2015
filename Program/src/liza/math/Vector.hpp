//==============================================================================
//
// Vector [Vector.hpp]
// Created : Shimizu Shoji
// MEMO:
// サイズをテンプレートで受け取る形式にしたいなー
// そうした場合に、演算などの最適化をサイズ1のベクタにのみ適用すれば
// その影響が全てのサイズに波及しないかな
// あえてキャスト演算子を使わない
// 暗黙の型キャストを制御できる気がしないため
//
//==============================================================================
#pragma once
#pragma warning( disable : 4201 )
#ifndef __HPP_LIZAMATHVECTOR_HPP__
#define __HPP_LIZAMATHVECTOR_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <assert.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace math {

//------------------------------------------------
// VECTOR2
//------------------------------------------------
template<typename T = float>
struct Vector2 {
	// ctor/dtor
	Vector2() {};
	Vector2( const Vector2& rhs );
	Vector2( T x, T y );
	explicit Vector2( const T* pValues );

	// cross
	inline T Cross( const Vector2& rhs ) const;

	// dot
	inline T Dot( const Vector2& rhs ) const;

	// length
	inline T Length( void ) const;
	inline T Length( const Vector2& rhs ) const;
	inline static T Length( const Vector2& lhs, const Vector2& rhs );
	inline T LengthSq( void ) const;
	inline T LengthSq( const Vector2& rhs ) const;
	inline static T LengthSq( const Vector2& lhs, const Vector2& rhs );

	// normalize
	inline Vector2& Normalize( void );
	inline Vector2 CreateNormalize( void ) const;
	inline Vector2& CreateNormalize( Vector2* pOut ) const;

	// casting
	inline T* ToData( void );
	inline const T* ToData( void ) const;

	// unary operator
	inline const Vector2 operator + () const;
	inline const Vector2 operator - () const;

	// binary operator
	inline const Vector2 operator * ( T rhs ) const;
	inline const Vector2 operator / ( T rhs ) const;
	inline const Vector2 operator + ( const Vector2& rhs ) const;
	inline const Vector2 operator - ( const Vector2& rhs ) const;

	// assignment opeartor
	inline Vector2& operator *= ( T rhs );
	inline Vector2& operator /= ( T rhs );
	inline Vector2& operator += ( const Vector2& rhs );
	inline Vector2& operator -= ( const Vector2& rhs );

	// bracket operator
	inline T& operator [] ( int index );
	inline const T& operator [] ( int index ) const;

	// logical operator
	inline bool operator == ( const Vector2& rhs ) const;
	inline bool operator != ( const Vector2& rhs ) const;

	// to when lhs is T
	template<typename T> friend inline const Vector2<T> operator * ( T lhs, const Vector2<T>& rhs );

	// property
	union {
		struct {
			T x, y;
		};
		T m[ 2 ];
	};

private:
	// impl bracket operator
	inline T& _ImplBracket( int index );
};

// include inline-header
#include "Vector2.inl"

// alias
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


//------------------------------------------------
// VECTOR3
//------------------------------------------------
template<typename T = float>
struct Vector3 {
	// ctor/dtor
	Vector3() {};
	Vector3( const Vector3& rhs );
	Vector3( T x, T y, T z );
	explicit Vector3( const T* pValues );

	// cross
	inline Vector3 Cross( const Vector3& rhs ) const;
	inline T Cross2D( const Vector3& rhs ) const;

	// dot
	inline T Dot( const Vector3& rhs ) const;

	// length
	inline T Length( void ) const;
	inline T Length( const Vector3& rhs ) const;
	inline static T Length( const Vector3& lhs, const Vector3& rhs );
	inline T LengthSq( void ) const;
	inline T LengthSq( const Vector3& rhs ) const;
	inline static T LengthSq( const Vector3& lhs, const Vector3& rhs );

	// normalize
	inline Vector3& Normalize( void );
	inline Vector3 CreateNormalize( void ) const;
	inline Vector3& CreateNormalize( Vector3* pOut ) const;

	// casting
	inline T* ToData( void );
	inline const T* ToData( void ) const;

	// unary operator
	inline const Vector3 operator + () const;
	inline const Vector3 operator - () const;

	// binary operator
	inline const Vector3 operator * ( T rhs ) const;
	inline const Vector3 operator / ( T rhs ) const;
	inline const Vector3 operator + ( const Vector3& rhs ) const;
	inline const Vector3 operator - ( const Vector3& rhs ) const;

	// assignment opeartor
	inline Vector3& operator *= ( T rhs );
	inline Vector3& operator /= ( T rhs );
	inline Vector3& operator += ( const Vector3& rhs );
	inline Vector3& operator -= ( const Vector3& rhs );

	// bracket operator
	inline T& operator [] ( int index );
	inline const T& operator [] ( int index ) const;

	// logical operator
	inline bool operator == ( const Vector3& rhs ) const;
	inline bool operator != ( const Vector3& rhs ) const;

	// to when lhs is T
	template<typename T> friend inline const Vector3<T> operator * ( T lhs, const Vector3<T>& rhs );

	// property
	union {
		struct {
			T x, y, z;
		};
		T m[ 3 ];
	};

private:
	// impl bracket operator
	inline T& _ImplBracket( int index );
};

// include inline-header
#include "Vector3.inl"

// alias
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;


//------------------------------------------------
// VECTOR4
//------------------------------------------------
template<typename T = float>
struct Vector4 {
	// ctor/dtor
	Vector4() {};
	Vector4( const Vector4& rhs );
	Vector4( T x, T y, T z, T w );
	explicit Vector4( const T* pValues );

	// method
	// dot
	inline T Dot( const Vector4& rhs ) const;

	// length
	inline T Length( void ) const;
	inline T Length( const Vector4& rhs ) const;
	inline static T Length( const Vector4& lhs, const Vector4& rhs );
	inline T LengthSq( void ) const;
	inline T LengthSq( const Vector4& rhs ) const;
	inline static T LengthSq( const Vector4& lhs, const Vector4& rhs );

	// normalize
	inline Vector4& Normalize( void );
	inline Vector4 CreateNormalize( void ) const;
	inline Vector4& CreateNormalize( Vector4* pOut ) const;

	// casting
	inline T* ToData( void );
	inline const T* ToData( void ) const;

	// unary operator
	inline const Vector4 operator + () const;
	inline const Vector4 operator - () const;

	// binary operator
	inline const Vector4 operator * ( T rhs ) const;
	inline const Vector4 operator / ( T rhs ) const;
	inline const Vector4 operator + ( const Vector4& rhs ) const;
	inline const Vector4 operator - ( const Vector4& rhs ) const;

	// assignment opeartor
	inline Vector4& operator *= ( T rhs );
	inline Vector4& operator /= ( T rhs );
	inline Vector4& operator += ( const Vector4& rhs );
	inline Vector4& operator -= ( const Vector4& rhs );

	// bracket operator
	inline T& operator [] ( int index );
	inline const T& operator [] ( int index ) const;

	// logical operator
	inline bool operator == ( const Vector4& rhs ) const;
	inline bool operator != ( const Vector4& rhs ) const;

	// to when lhs is T
	template<typename T> friend inline const Vector4<T> operator * ( T lhs, const Vector4<T>& rhs );

	// property
	union {
		struct {
			T x, y, z, w;
		};
		T m[ 4 ];
	};

private:
	// impl bracket operator
	inline T& _ImplBracket( int index );
};

// include inline-header
#include "Vector4.inl"

// alias
typedef Vector4<int> Vector4i;
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;

	} // namespace math
} // namespace liza


#endif // __HPP_LIZAMATHVECTOR_HPP__