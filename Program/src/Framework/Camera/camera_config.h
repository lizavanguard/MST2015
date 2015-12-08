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
const float kFov = D3DX_PI / 2.0f;
const float kAspect = kWindowWidth / (float)(kWindowHeight);
const float kNear = 10.0f;
const float kFar = 100000.0f;

const unsigned int kCameraMax = 3;
const D3DXVECTOR3 kInitialEyePosition[kCameraMax] = {
  {0.0f, 1000.0f, -2000.0f},
  {0.0f, 1000.0f, -100.0f},
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
