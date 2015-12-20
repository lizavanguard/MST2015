//==============================================================================
//
// ColorGrading
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "ColorGrading.h"

#include "Framework/Input/InputKeyboard.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
post_effect::ColorGrading::ColorGrading()
    : PostEffect("color_grading")
    , ycbcr(1.0f, 1.0f, 1.0f)
    , is_applied_(true) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
post_effect::ColorGrading::~ColorGrading() {
}

//------------------------------------------------
// Process
//------------------------------------------------
void post_effect::ColorGrading::_Process(LPDIRECT3DTEXTURE9 p_source) {
  auto p_shader = this->GetShader();

  D3DXVECTOR3 data(1.0, 1.0f, 1.0f);
  if (is_applied_) {
    data = ycbcr;
  }
  p_shader->SetFloatArray("uniform_ycbcr_rate", data, 3);
  p_shader->SetTexture("texture_decale", p_source);

#ifdef _DEBUG
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeed = 0.001f;
  if (keyboard.IsPress(DIK_F3)) {
    if (keyboard.IsPress(DIK_LSHIFT)) {
      ycbcr.x = std::max<float>(ycbcr.x - kSpeed, 0.0f);
    }
    else {
      ycbcr.x = ycbcr.x + kSpeed;
    }
  }
  if (keyboard.IsPress(DIK_F4)) {
    if (keyboard.IsPress(DIK_LSHIFT)) {
      ycbcr.y = std::max<float>(ycbcr.y - kSpeed, 0.0f);
    }
    else {
      ycbcr.y = ycbcr.y + kSpeed;
    }
  }
  if (keyboard.IsPress(DIK_F5)) {
    if (keyboard.IsPress(DIK_LSHIFT)) {
      ycbcr.z = std::max<float>(ycbcr.z - kSpeed, 0.0f);
    }
    else {
      ycbcr.z = ycbcr.z + kSpeed;
    }
  }

  if (keyboard.IsTrigger(DIK_F6)) {
    is_applied_ = !is_applied_;
  }

  DebugProc::Print("[%s]YCbCr[%.4f, %.4f, %.4f]\n", (is_applied_ ? "適用中" :"未適用"),  ycbcr.x, ycbcr.y, ycbcr.z);
#endif
}
