//==============================================================================
//
// ObjectFBXModel
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
// class delcaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class FbxModel;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ObjectFBXModel : public ObjectBase {
public:
  // ctor
  ObjectFBXModel(const char* p_filename);

  // dtor
  virtual ~ObjectFBXModel();

  void SetupAnimation(int index);
  void SetupAnimationLoop(bool loop_flg);

protected:
  virtual void _Update(float elapsed_time) override;
  virtual void _Draw(void) override;

protected:
  // 必要に応じてアニメーション設定を行って下さい
  //virtual void _SetupAnimation(void) {};

  // property
  FbxModel* p_fbx_model_;
};

using ObjectFbxModelFactory = liza::generic::Factory<ObjectFBXModel>;
