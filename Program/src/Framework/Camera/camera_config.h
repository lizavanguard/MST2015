//==============================================================================
//
// CameraConfig
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "window_config.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
const float kFov = D3DXToRadian(50.0f);
const float kAspect = kWindowWidth / (float)(kWindowHeight);
const float kNear = 5.0f;
const float kFar = 70000.0f;

const unsigned int kCameraMax = 3;
const D3DXVECTOR3 kInitialEyePosition[kCameraMax] = {
  {0.0f, 1000.0f, -2000.0f},
  {1.0f, 1000.0f,  6000.0f},
  {1000.0f, 1000.0f, 1000.0f}
};
const D3DXVECTOR3 kInitialAtPosition[kCameraMax] = {
  {0.0f, 0.0f, 0.0f},
  {0.0f, 0.0f, 0.0f},
  {0.0f, 0.0f, 0.0f}
};
static const char* kCameraName[kCameraMax] = {
  "MAIN_1",
  "MAIN_2",
  "MAIN_3"
};
static const char* kSkyboxCameraName = "SKYBOX_CAMERA";
