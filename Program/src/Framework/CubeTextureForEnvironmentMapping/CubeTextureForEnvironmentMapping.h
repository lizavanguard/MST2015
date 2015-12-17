//==============================================================================
//
// CubeTextureForEnvironmentMapping
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/game/directx/render_target_holder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace cube_mapping {
  static const char* kCubeCamera = "CUBE_CAMERA";
}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CubeTextureForEnvironmentMapping {
public:

  // inner class
  class ObjectDrawer {
  public:
    virtual ~ObjectDrawer() {}
    virtual void _DrawObject(void) = 0;
  };

public:
  // ctor
  CubeTextureForEnvironmentMapping(ObjectDrawer* p_object_drawer);

  // dtor
  ~CubeTextureForEnvironmentMapping();

  // Draw
  void Draw(const D3DXVECTOR3& position);

  // get
  LPDIRECT3DTEXTURE9 GetCubeTexture(void) const { return reinterpret_cast<LPDIRECT3DTEXTURE9>(pp_dynamic_cube_texture_); }

//private:
  // property
  IDirect3DCubeTexture9* pp_dynamic_cube_texture_;
  ObjectDrawer* p_object_drawer_;
};
