//==============================================================================
//
// Inline Header of Vector2 [Vector2.inl]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAMATHVECTOR2_INL__
#define __INL_LIZAMATHVECTOR2_INL__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Vector.hpp"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
template<typename T>
Vector2<T>::Vector2( const Vector2& rhs ) : x( rhs.x ), y( rhs.y ) {
}


template<typename T>
Vector2<T>::Vector2( const T _x, const T _y ) : x( _x ), y( _y ) {
}


template<typename T>
Vector2<T>::Vector2( const T* const pValues ) {
	assert( pValues != nullptr );
	x = pValues[ 0 ];
	y = pValues[ 1 ];
}


//------------------------------------------------
// cross
//------------------------------------------------
template<typename T>
T Vector2<T>::Cross( const Vector2& rhs ) const {
	return x * rhs.y - y * rhs.x;
}


//------------------------------------------------
// dot
//------------------------------------------------
template<typename T>
T Vector2<T>::Dot( const Vector2& rhs ) const {
	return x * rhs.x + y * rhs.y;
}


//------------------------------------------------
// length
//------------------------------------------------
template<typename T>
T Vector2<T>::Length( void ) const {
	return sqrt( x * x + y * y );
}


template<typename T>
T Vector2<T>::Length( const Vector2& rhs ) const {
	return Vector2( *this - rhs ).Length();
}


template<typename T>
T Vector2<T>::Length( const Vector2& lhs, const Vector2& rhs ) {
	return lhs.Length( rhs );
}


template<typename T>
T Vector2<T>::LengthSq( void ) const {
	return x * x + y * y;
}


template<typename T>
T Vector2<T>::LengthSq( const Vector2& rhs ) const {
	return Vector2( *this - rhs ).LengthSq();
}


template<typename T>
T Vector2<T>::LengthSq( const Vector2& lhs, const Vector2& rhs ) {
	return lhs.LengthSq( rhs );
}


//------------------------------------------------
// normalize
//------------------------------------------------
template<typename T>
Vector2<T>& Vector2<T>::Normalize( void ) {
	return *this /= Length();
}


template<typename T>
Vector2<T> Vector2<T>::CreateNormalize( void ) const {
	return Vector2( *this ).Normalize();
}


template<typename T>
Vector2<T>& Vector2<T>::CreateNormalize( Vector2* const pOut ) const {
	*pOut = *this;
	return pOut->Normalize();
}


//------------------------------------------------
// casting
//------------------------------------------------
template<typename T>
T* Vector2<T>::ToData( void ) {
	return m;
}


template<typename T>
const T* Vector2<T>::ToData( void ) const {
	return m;
}


//------------------------------------------------
// unary operator
//------------------------------------------------
template<typename T>
const Vector2<T> Vector2<T>::operator + () const {
	return *this;
}


template<typename T>
const Vector2<T> Vector2<T>::operator - () const {
	return Vector2( -x, -y );
}


//------------------------------------------------
// binary operator
//------------------------------------------------
template<typename T>
const Vector2<T> Vector2<T>::operator * ( const T rhs ) const {
	return Vector2( *this ) *= rhs;
}


template<typename T>
const Vector2<T> Vector2<T>::operator / ( const T rhs ) const {
	return Vector2( *this ) /= rhs;
}


template<typename T>
const Vector2<T> Vector2<T>::operator + ( const Vector2& rhs ) const {
	return Vector2( *this ) += rhs;
}


template<typename T>
const Vector2<T> Vector2<T>::operator - ( const Vector2& rhs ) const {
	return Vector2( *this ) -= rhs;
}


//------------------------------------------------
// assignment operator
//------------------------------------------------
template<typename T>
Vector2<T>& Vector2<T>::operator *= ( const T rhs ) {
	x *= rhs;
	y *= rhs;
	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator /= ( const T rhs ) {
	T inv = 1 / rhs;
	x *= inv;
	y *= inv;
	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator += ( const Vector2& rhs ) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}


template<typename T>
Vector2<T>& Vector2<T>::operator -= ( const Vector2& rhs ) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}


//------------------------------------------------
// bracket operator
//------------------------------------------------
template<typename T>
T& Vector2<T>::operator [] ( const int index ) {
	return _ImplBracket( index );
};


template<typename T>
const T& Vector2<T>::operator [] ( const int index ) const {
	return _ImplBracket( index );
}


//------------------------------------------------
// logical operator
//------------------------------------------------
template<typename T>
bool Vector2<T>::operator == ( const Vector2& rhs ) const {
	return x == rhs.x && y == rhs.y;
}


template<typename T>
bool Vector2<T>::operator != ( const Vector2& rhs ) const {
	return !( *this == rhs );
}


//------------------------------------------------
// to when lhs is T
//------------------------------------------------
template<typename T>
const Vector2<T> operator * ( const T lhs, const Vector2<T>& rhs ) {
	return Vector2<T>( rhs ) *= lhs;
}


//------------------------------------------------
// impl bracket operator
//------------------------------------------------
template<typename T>
inline T& Vector2<T>::_ImplBracket( const int index ) {
	assert( index < 2 );
	return m[ index ];
}


#endif // __INL_LIZAMATHVECTOR2_INL__