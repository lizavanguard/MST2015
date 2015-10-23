//==============================================================================
//
// ModelManager
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
ModelManager::ModelManager() : p_container_(nullptr) {
  static const char* kModelDirectoryPath = "data/Model/x/";
  p_container_ = new ContainerType(kModelDirectoryPath, [](const char* p_filename, DataType* p_data){
    LPD3DXMESH p_mesh;
    LPD3DXBUFFER p_materials;
    DWORD num_materials;
    liza::game::directx::LoadMeshFromX(DeviceHolder::Instance().GetDevice(), p_filename, &p_mesh, &p_materials, &num_materials);
    *p_data = new _XModel(p_mesh, p_materials, num_materials);
  });
}

//------------------------------------------------
// dtor
//------------------------------------------------
ModelManager::~ModelManager() {
  SafeDelete(p_container_);
}
