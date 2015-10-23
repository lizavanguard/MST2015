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

#include "Framework/Model/model_manager.h"

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
  XModelData* p_xmodel_data_;
};
