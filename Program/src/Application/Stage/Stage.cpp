//==============================================================================
//
// Stage
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Stage.h"

#include "Framework/Object/object_model.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kModelName = "stage_06";
  const int kConnectionMax = 4;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Stage::Stage() {
  const float kStageOffset = 35000.0f;
  for (int i = 0; i < kConnectionMax; ++i) {
    auto stage = new ObjectModel(kModelName);
    stage->SetPosition(D3DXVECTOR3(0.0f, 0.0f, kStageOffset * i));
    AttachChild(stage);
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
Stage::~Stage() {
}

//------------------------------------------------
// _Update
//------------------------------------------------
void Stage::_Update(float elapsed_time) {

}

//------------------------------------------------
// _Draw
//------------------------------------------------
void Stage::_Draw(void) {
}
