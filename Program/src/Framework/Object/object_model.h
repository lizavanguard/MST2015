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
#include "liza/generic/factory.hpp"
#include "Framework/Model/model_manager.h"

#include "object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectModel : public ObjectBase {
public:
  // ctor
  ObjectModel(const char* p_filename);

  // dtor
  virtual ~ObjectModel();

private:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

protected:
  // property
  XModelData* p_xmodel_data_;
  LPD3DXEFFECT p_shader_;
};

using ObjectModelFactory = liza::generic::Factory<ObjectModel>;