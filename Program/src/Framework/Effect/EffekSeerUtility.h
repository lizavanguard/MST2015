//==============================================================================
//
// EffekseerUtility
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <Effekseer.h>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// prototype
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace EffekseerUtility {

Effekseer::Vector3D VectorToEffekSeer(const D3DXVECTOR3& v);
D3DXVECTOR3 VectorToD3DX(const Effekseer::Vector3D& v);

Effekseer::Matrix44 MatrixToEffekSeer(const D3DXMATRIX& m);

}