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
  // ��������݂̂Ȃ�ŏ���
  p_fbx_model_->SetAnimationCount(2);
  p_fbx_model_->SetAnimationFlame(0, 70.0f);
  p_fbx_model_->SetAnimationFlame(1, 110.0f);
  p_fbx_model_->SetAnimationSpeed(0.8f);
  p_fbx_model_->AnimationLoopOff();
  p_fbx_model_->SetAnimation(0);
  p_fbx_model_->AnimationStop();
  //_SetupAnimation();
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
  p_fbx_model_->SetPosition(GetWorldPosition());
  p_fbx_model_->SetRotation(rotation_);
  p_fbx_model_->SetRotationMatrix(rotation_matrix_);
  p_fbx_model_->SetScale(scale_);
  p_fbx_model_->Update();
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectFBXModel::_Draw(void) {
  p_fbx_model_->Draw();
}

void ObjectFBXModel::SetupAnimation(int index) {
  p_fbx_model_->SetAnimation(index);
  p_fbx_model_->AnimationPlay();
}

void ObjectFBXModel::SetupAnimationLoop(bool loop_flg) {
  if( loop_flg ) {
    p_fbx_model_->AnimationLoopOn();
  }
  else {
    p_fbx_model_->AnimationLoopOff();
  }
}