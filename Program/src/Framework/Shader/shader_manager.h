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

#include "Framework/Utility/DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _ShaderManager {
private:
  using ContainerType = DataFinder<LPD3DXEFFECT>;

public:
  // ctor
  _ShaderManager();

  // dtor
  ~_ShaderManager();

  // get
  LPD3DXEFFECT FindShader(const ContainerType::KeyType& shader_name);

private:
  ContainerType* p_finder_;
};

using ShaderManager = liza::generic::SingletonHolder<_ShaderManager>;
