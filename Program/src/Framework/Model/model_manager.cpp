//==============================================================================
//
// _ModelManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "model_manager.h"

#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_ModelManager::_ModelManager() : p_container_(nullptr) {
  static const char* kModelDirectoryPath = "data/Model/x/";
  p_container_ = new ContainerType(kModelDirectoryPath, [](const char* p_filename, DataType* p_data){
    *p_data = new _XModelData(p_filename);
  });
}

//------------------------------------------------
// dtor
//------------------------------------------------
_ModelManager::~_ModelManager() {
  SafeDelete(p_container_);
}

//------------------------------------------------
// ƒtƒ@ƒCƒ‹–¼‚ÅŒŸõ
//------------------------------------------------
_ModelManager::DataType _ModelManager::Find(const KeyType& filename) {
  return p_container_->Find(filename);
}
