//==============================================================================
//
// Object3D
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_base.h"
#include "creator.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3D : public ObjectBase, public Creator<Object3D> {
public:
  // ctor
  Object3D(const char* p_filename);

  // dtor
  virtual ~Object3D();

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  // property
  LPD3DXEFFECT p_shader_;
  PDIRECT3DVERTEXDECLARATION9 p_declaration_;
  LPDIRECT3DTEXTURE9 p_texture_;
};
