//==============================================================================
//
// ShaderManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/SingletonHolder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _ShaderManager {
private:
  using KeyType = std::string;
  using DataType = LPD3DXEFFECT;
  using ContainerType = std::map <KeyType, DataType>;

public:
  // ctor
  _ShaderManager();

  // dtor
  ~_ShaderManager();

  // get
  LPD3DXEFFECT FindShader(const KeyType& shader_name);

private:
  ContainerType container_;
};

using ShaderManager = liza::generic::SingletonHolder<_ShaderManager>;
