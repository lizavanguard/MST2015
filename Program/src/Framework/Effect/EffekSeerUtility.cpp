//==============================================================================
//
// EffekSeerUtility
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "EffekSeerUtility.h"

//==============================================================================
// function implementation
//==============================================================================
Effekseer::Vector3D EffekSeerUtility::VectorToEffekSeer(const D3DXVECTOR3& v) {
  return Effekseer::Vector3D(v.x, v.y, v.z);
}

D3DXVECTOR3 EffekSeerUtility::VectorToD3DX(const Effekseer::Vector3D& v) {
  return D3DXVECTOR3(v.X, v.Y, v.Z);
}

Effekseer::Matrix44 EffekSeerUtility::MatrixToEffekSeer(const D3DXMATRIX& m) {
  Effekseer::Matrix44 temp;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      temp.Values[i][j] = m.m[i][j];
    }
  }
  return temp;
}
