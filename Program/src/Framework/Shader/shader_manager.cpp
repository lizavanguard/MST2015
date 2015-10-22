//==============================================================================
//
// _ShaderManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "shader_manager.h"

#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_ShaderManager::_ShaderManager() : p_finder_(nullptr) {
  static const char* kStartPath = "./hlsl/";
  p_finder_ = new ContainerType(kStartPath, [](const char* p_filename, LPD3DXEFFECT* pp_effect) {
    liza::game::directx::LoadShader(DeviceHolder::Instance().GetDevice(), p_filename, pp_effect); });
}

//------------------------------------------------
// dtor
//------------------------------------------------
_ShaderManager::~_ShaderManager() {
  SafeDelete(p_finder_);
}

//------------------------------------------------
// get
//------------------------------------------------
LPD3DXEFFECT _ShaderManager::FindShader(const ContainerType::KeyType& shader_name) {
  return p_finder_->Find(shader_name);
}
