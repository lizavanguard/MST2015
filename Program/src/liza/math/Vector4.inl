//==============================================================================
//
// Inline Header of Vector4 [Vector4.inl]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAMATHVECTOR4_INL__
#define __INL_LIZAMATHVECTOR4_INL__
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
Vector4<T>::Vector4( const Vector4& rhs ) : x( rhs.x ), y( rhs.y ), z( rhs.z ), w( rhs.w ) {
}


template<typename T>
Vector4<T>::Vector4( const T _x, const T _y, const T _z, const T _w ) : x( _x ), y( _y ), z( _z ), w( _w ) {
}


template<typename T>
Vector4<T>::Vector4( const T* const pValues ) {
	assert( pValues != nullptr );
	x = pValues[ 0 ];
	y = pValues[ 1 ];
	z = pValues[ 2 ];
	w = pValues[ 3 ];
}


//------------------------------------------------
// dot
//------------------------------------------------
template<typename T>
T Vector4<T>::Dot( const Vector4& rhs ) const {
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}


//------------------------------------------------
// length
//------------------------------------------------
template<typename T>
T Vector4<T>::Length( void ) const {
	return sqrt( x * x + y * y + z * z + w * w );
}


template<typename T>
T Vector4<T>::Length( const Vector4& rhs ) const {
	return Vector4( *this - rhs ).Length();
}


template<typename T>
T Vector4<T>::Length( const Vector4& lhs, const Vector4& rhs ) {
	return lhs.Length( rhs );
}


template<typename T>
T Vector4<T>::LengthSq( void ) const {
	return x * x + y * y + z * z + w * w;
}


template<typename T>
T Vector4<T>::LengthSq( const Vector4& rhs ) const {
	return Vector4( *this - rhs ).LengthSq();
}


template<typename T>
T Vector4<T>::LengthSq( const Vector4& lhs, const Vector4& rhs ) {
	return lhs.LengthSq( rhs );
}


//------------------------------------------------
// normalzie
//------------------------------------------------
template<typename T>
Vector4<T>& Vector4<T>::Normalize( void ) {
	return *this /= Length();
}

template<typename T>
Vector4<T> Vector4<T>::CreateNormalize( void ) const {
	return Vector4( *this ).Normalize();
}

template<typename T>
Vector4<T>& Vector4<T>::CreateNormalize( Vector4* const pOut ) const {
	*pOut = *this;
	return pOut->Normalize;
}


//------------------------------------------------
// casting
//------------------------------------------------
template<typename T>
T* Vector4<T>::ToData( void ) {
	return m;
}


template<typename T>
const T* Vector4<T>::ToData( void ) const {
	return m;
}


//------------------------------------------------
// unary operator
//------------------------------------------------
template<typename T>
const Vector4<T> Vector4<T>::operator + () const {
	return *this;
}


template<typename T>
const Vector4<T> Vector4<T>::operator - () const {
	return Vector4<T>( -x, -y, -z, -w );
}


//------------------------------------------------
// binary operator
//------------------------------------------------
template<typename T>
const Vector4<T> Vector4<T>::operator * ( const T rhs ) const {
	return Vector4( *this ) *= rhs;
}


template<typename T>
const Vector4<T> Vector4<T>::operator / ( const T rhs ) const {
	return Vector4( *this ) /= rhs;
}


template<typename T>
const Vector4<T> Vector4<T>::operator + ( const Vector4& rhs ) const {
	return Vector4( *this ) += rhs;
}


template<typename T>
const Vector4<T> Vector4<T>::operator - ( const Vector4& rhs ) const {
	return Vector4( *this ) -= rhs;
}


//------------------------------------------------
// assignment operator
//------------------------------------------------
template<typename T>
Vector4<T>& Vector4<T>::operator *= ( const T rhs ) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}


template<typename T>
Vector4<T>& Vector4<T>::operator /= ( const T rhs ) {
	T inv = 1 / rhs;
	x *= inv;
	y *= inv;
	z *= inv;
	w *= inv;
	return *this;
}


template<typename T>
Vector4<T>& Vector4<T>::operator += ( const Vector4& rhs ) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}


template<typename T>
Vector4<T>& Vector4<T>::operator -= ( const Vector4& rhs ) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}


//------------------------------------------------
// bracket operator
//------------------------------------------------
template<typename T>
T& Vector4<T>::operator [] ( const int index ) {
	return _ImplBracket( index );
};


template<typename T>
const T& Vector4<T>::operator [] ( const int index ) const {
	return _ImplBracket( index );
}


//------------------------------------------------
// logical operator
//------------------------------------------------
template<typename T>
bool Vector4<T>::operator == ( const Vector4& rhs ) const {
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}


template<typename T>
bool Vector4<T>::operator != ( const Vector4& rhs ) const {
	return !( *this == rhs );
}


//------------------------------------------------
// to when lhs is T
//------------------------------------------------
template<typename T>
const Vector4<T> operator * ( const T lhs, const Vector4<T>& rhs ) {
	return Vector4<T>( rhs ) *= lhs;
}


//------------------------------------------------
// impl bracket operator
//------------------------------------------------
template<typename T>
inline T& Vector4<T>::_ImplBracket( const int index ) {
	assert( index < 4 );
	return m[ index ];
}


#endif // __INL_LIZAMATHVECTOR4_INL__