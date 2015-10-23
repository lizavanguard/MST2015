//==============================================================================
//
// ModelManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Utility/DataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ModelManager {
public:
  struct _XModel {
    _XModel(LPD3DXMESH _p_mesh, LPD3DXBUFFER _p_materials, DWORD _num_materials)
      : p_mesh(_p_mesh), p_materials(_p_materials), num_materials(_num_materials) {
    }

    ~_XModel() {
      SafeRelease(p_mesh);
      SafeRelease(p_materials);
    }

    LPD3DXMESH p_mesh;
    LPD3DXBUFFER p_materials;
    DWORD num_materials;
  };

  using DataType = _XModel*;
  using ContainerType = DataLoader<DataType, UsingDelete>;

public:
  // ctor
  ModelManager();

  // dtor
  ~ModelManager();

private:
  ContainerType* p_container_;
};
