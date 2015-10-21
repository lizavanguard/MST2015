//==============================================================================
//
// ObjectModel
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "creator.h"
#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectModel : public ObjectBase, public Creator<ObjectModel> {
public:
  // ctor
  ObjectModel(const char* p_filename);

  // dtor
  virtual ~ObjectModel();

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

  // property
  LPD3DXMESH p_mesh_;
  LPD3DXBUFFER p_materials_;
  DWORD num_materials_;
};
