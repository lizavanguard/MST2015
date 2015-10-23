//==============================================================================
//
// _ModelManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/SingletonHolder.hpp"

#include "Framework/Utility/DataLoader.hpp"
#include "Framework/Texture/texture_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _ModelManager {
public:
  class _XModelData {
  public:
    _XModelData(const char* p_filename) : p_mesh(nullptr), p_materials(nullptr), num_materials(0) {
      auto p_device = DeviceHolder::Instance().GetDevice();
      liza::game::directx::LoadMeshFromX(p_device, p_filename, &p_mesh, &p_materials, &num_materials);
      p_textures.reserve(num_materials);

      D3DMATERIAL9 material_old;
      p_device->GetMaterial(&material_old);
      D3DXMATERIAL* p_d3dx_material = (D3DXMATERIAL*)p_materials->GetBufferPointer();
      for (unsigned int i = 0; i < num_materials; ++i) {
        if (p_d3dx_material[i].pTextureFilename) {
          p_textures.push_back(TextureManager::Instance().Find("Model", p_d3dx_material[i].pTextureFilename));
        }
        else {
          p_textures.push_back(nullptr);
        }
      }
      p_device->SetMaterial(&material_old);
    }

    ~_XModelData() {
      SafeRelease(p_mesh);
      SafeRelease(p_materials);
    }

    LPD3DXMESH p_mesh;
    LPD3DXBUFFER p_materials;
    DWORD num_materials;
    std::vector<LPDIRECT3DTEXTURE9> p_textures;
  };

  using DataType = _XModelData*;
  using ContainerType = DataLoader<DataType, UsingDelete>;
  using KeyType = ContainerType::KeyType;

public:
  // ctor
  _ModelManager();

  // dtor
  ~_ModelManager();

  // ÉtÉ@ÉCÉãñºÇ≈åüçı
  DataType Find(const KeyType& filename);

private:
  ContainerType* p_container_;
};

using XModelData = _ModelManager::_XModelData;
using ModelManager = liza::generic::SingletonHolder<_ModelManager>;
