//==============================================================================
//
// ObjectFBXModel
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_fbx_model.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"

#include "FBX/fbx_model.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectFBXModel::ObjectFBXModel(const char* p_filename) : p_fbx_model_(nullptr) {
  p_fbx_model_ = new FbxModel(DeviceHolder::Instance().GetDevice());

  std::string path = "data/Model/fbx/";
  path += p_filename;
  p_fbx_model_->Load(path);

  p_fbx_model_->AnimationStop();
  _SetupAnimation();
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectFBXModel::~ObjectFBXModel() {
  SafeDelete(p_fbx_model_);
}


//------------------------------------------------
// _Update
//------------------------------------------------
void ObjectFBXModel::_Update(const float elapsed_time) {
  p_fbx_model_->SetPosition(position_);
  p_fbx_model_->SetRotation(rotation_);
  p_fbx_model_->SetRotationMatrix(rotation_matrix_);
  p_fbx_model_->Update();
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectFBXModel::_Draw(void) {
  p_fbx_model_->Draw();
}
