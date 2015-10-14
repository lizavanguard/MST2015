//==============================================================================
//
// Inline Header of Vector3 [Vector3.inl]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAMATHVECTOR3_INL__
#define __INL_LIZAMATHVECTOR3_INL__
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
Vector3<T>::Vector3( const Vector3& rhs ) : x( rhs.x ), y( rhs.y ), z( rhs.z ) {
}


template<typename T>
Vector3<T>::Vector3( const T _x, const T _y, const T _z ) : x( _x ), y( _y ), z( _z ) {
}


template<typename T>
Vector3<T>::Vector3( const T* const pValues ) {
	assert( pValues != nullptr );
	x = pValues[ 0 ];
	y = pValues[ 1 ];
	z = pValues[ 2 ];
}


//------------------------------------------------
// cross
//------------------------------------------------
template<typename T>
Vector3<T> Vector3<T>::Cross( const Vector3& rhs ) const {
	return Vector3<T>( y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x );
}


template<typename T>
T Vector3<T>::Cross2D( const Vector3& rhs ) const {
	return x * rhs.z - z * rhs.x;
}


//------------------------------------------------
// dot
//------------------------------------------------
template<typename T>
T Vector3<T>::Dot( const Vector3& rhs ) const {
	return x * rhs.x + y * rhs.y + z * rhs.z;
}


//------------------------------------------------
// length
//------------------------------------------------
template<typename T>
T Vector3<T>::Length( void ) const {
	return sqrt( x * x + y * y + z * z );
}


template<typename T>
T Vector3<T>::Length( const Vector3& rhs ) const {
	return Vector3( *this - rhs ).Length();
}


template<typename T>
T Vector3<T>::Length( const Vector3& lhs, const Vector3& rhs ) {
	return lhs.Length( rhs );
}


template<typename T>
T Vector3<T>::LengthSq( void ) const {
	return x * x + y * y + z * z;
}


template<typename T>
T Vector3<T>::LengthSq( const Vector3& rhs ) const {
	return Vector3( *this - rhs ).LengthSq();
}


template<typename T>
T Vector3<T>::LengthSq( const Vector3& lhs, const Vector3& rhs ) {
	return lhs.LengthSq( rhs );
}


//------------------------------------------------
// normalize
//------------------------------------------------
template<typename T>
Vector3<T>& Vector3<T>::Normalize( void ) {
	return *this /= Length();
}


template<typename T>
Vector3<T> Vector3<T>::CreateNormalize( void ) const {
	return Vector3( *this ).Normalize();
}

template<typename T>
Vector3<T>& Vector3<T>::CreateNormalize( Vector3* const pOut ) const {
	*pOut = *this;
	return pOut->Normalize();
}


//------------------------------------------------
// casting
//------------------------------------------------
template<typename T>
T* Vector3<T>::ToData( void ) {
	return m;
}


template<typename T>
const T* Vector3<T>::ToData( void ) const {
	return m;
}


//------------------------------------------------
// unary operator
//------------------------------------------------
template<typename T>
const Vector3<T> Vector3<T>::operator + () const {
	return *this;
}


template<typename T>
const Vector3<T> Vector3<T>::operator - () const {
	return Vector3( -x, -y, -z );
}


//------------------------------------------------
// binary operator
//------------------------------------------------
template<typename T>
const Vector3<T> Vector3<T>::operator * ( const T rhs ) const {
	return Vector3( *this ) *= rhs;
}


template<typename T>
const Vector3<T> Vector3<T>::operator / ( const T rhs ) const {
	return Vector3( *this ) /= rhs;
}


template<typename T>
const Vector3<T> Vector3<T>::operator + ( const Vector3& rhs ) const {
	return Vector3( *this ) += rhs;
}


template<typename T>
const Vector3<T> Vector3<T>::operator - ( const Vector3& rhs ) const {
	return Vector3( *this ) -= rhs;
}


//------------------------------------------------
// assignment operator
//------------------------------------------------
template<typename T>
Vector3<T>& Vector3<T>::operator *= ( const T rhs ) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}


template<typename T>
Vector3<T>& Vector3<T>::operator /= ( const T rhs ) {
	T inv = 1 / rhs;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}


template<typename T>
Vector3<T>& Vector3<T>::operator += ( const Vector3& rhs ) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}


template<typename T>
Vector3<T>& Vector3<T>::operator -= ( const Vector3& rhs ) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}


//------------------------------------------------
// bracket operator
//------------------------------------------------
template<typename T>
T& Vector3<T>::operator [] ( const int index ) {
	return _ImplBracket( index );
};


template<typename T>
const T& Vector3<T>::operator [] ( const int index ) const {
	return _ImplBracket( index );
}


//------------------------------------------------
// logical operator
//------------------------------------------------
template<typename T>
bool Vector3<T>::operator == ( const Vector3& rhs ) const {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}


template<typename T>
bool Vector3<T>::operator != ( const Vector3& rhs ) const {
	return !( *this == rhs );
}


//------------------------------------------------
// to when lhs is T
//------------------------------------------------
template<typename T>
const Vector3<T> operator * ( const T lhs, const Vector3<T>& rhs ) {
	return Vector3<T>( rhs ) *= lhs;
}


//------------------------------------------------
// impl bracket operator
//------------------------------------------------
template<typename T>
inline T& Vector3<T>::_ImplBracket( const int index ) {
	assert( index < 3 );
	return m[ index ];
}


#endif // __INL_LIZAMATHVECTOR3_INL__