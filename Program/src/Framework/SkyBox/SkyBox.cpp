//==============================================================================
//
// SkyBox
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SkyBox.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Object/object3d.h"
#include "Framework/Texture/texture_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 100.0f;
  const float kSizeHalf = kSize / 2.0f;
  const float kSizeOffset = kSizeHalf - 0.5f;
  const char* kSkyboxCameraName = "SKYBOX_CAMERA";

  const unsigned int kNumFaces = 6;

// Skybox name
#define SKYBOX_NAME "stratosphere"

#define _SKYBOX_TEXTURE_NAMES(x) "SkyBox_" SKYBOX_NAME "/" SKYBOX_NAME "_" #x ".tga"
#define SKYBOX_TEXTURE_NAMES \
  _SKYBOX_TEXTURE_NAMES(ft), \
  _SKYBOX_TEXTURE_NAMES(bk), \
  _SKYBOX_TEXTURE_NAMES(rt), \
  _SKYBOX_TEXTURE_NAMES(lf), \
  _SKYBOX_TEXTURE_NAMES(up), \
  _SKYBOX_TEXTURE_NAMES(dn)

  const char* kTexturenames[kNumFaces] = {
    SKYBOX_TEXTURE_NAMES
  };
  const char* kSkyboxname = "Skybox_" SKYBOX_NAME;

#undef _SKYBOX_TEXTURE_NAMES
#undef SKYBOX_TEXTURE_NAMES

  const D3DXVECTOR3 kPoses[kNumFaces] = {
    D3DXVECTOR3(0, 0, kSizeOffset),	// Z+
    D3DXVECTOR3(0, 0, -kSizeOffset),	// Z-
    D3DXVECTOR3(-kSizeOffset, 0, 0),	// X+
    D3DXVECTOR3(kSizeOffset, 0, 0),	// X-
    D3DXVECTOR3(0, kSizeOffset, 0),	// Y+
    D3DXVECTOR3(0, -kSizeOffset, 0),	// Y-
  };

  const D3DXVECTOR3 kRots[kNumFaces] = {
    D3DXVECTOR3(0, 0, 0),
    D3DXVECTOR3(0, liza::math::kPIf, 0),
    D3DXVECTOR3(0, -liza::math::kPIHalff, 0),
    D3DXVECTOR3(0, liza::math::kPIHalff, 0),

    D3DXVECTOR3(-liza::math::kPIHalff, liza::math::kPIf, +liza::math::kPIHalff),
    D3DXVECTOR3( liza::math::kPIHalff, liza::math::kPIf, -liza::math::kPIHalff),
  };
}

#include "Framework/Camera/camera_steering_set.h"
#include "Framework/Object/root.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SkyBox::SkyBox() : p_camera_steering_(nullptr) {
  // load texture
  TextureManager::Instance().Load(kSkyboxname);

  // create a skybox camera
  Camera& main_camera = CameraManager::Instance().FindUsingHandle(0);
  D3DXVECTOR3 at = main_camera.CalculateCameraDirection();
  D3DXVECTOR3 eye(-at);
  Camera* p_camera = new Camera(eye, at);
  CameraManager::Instance().Register(kSkyboxCameraName, p_camera);

  p_camera_steering_ = new CameraSteeringSet();
  p_camera->AssignCameraSteering(p_camera_steering_);

  // create faces
  const _CameraManager::CameraHandle camera_handle = CameraManager::Instance().GetCameraHandle(kSkyboxCameraName);
  for (unsigned int face_count = 0; face_count < kNumFaces; ++face_count) {
    auto object = Object3DFactory::Create(kTexturenames[face_count]);
    object->SetPosition(kPoses[face_count]);
    object->SetRotation(kRots[face_count]);
    static const float kOffset = 0.0005f;
    const float min = kOffset;
    const float max = 1 - kOffset;
    object->SetUVCorner(min, min, max, max);
    object->OffBottomCentered();
    object->SetCameraHandle(camera_handle);
    AttachChild(object);
  }
  is_child_auto_drawed_ = false;
}

//------------------------------------------------
// dtor
//------------------------------------------------
SkyBox::~SkyBox() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void SkyBox::_Update(const float) {
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SkyBox::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  D3DXMATRIX view_old;
  p_device->GetTransform(D3DTS_VIEW, &view_old);
  p_device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  auto& camera = CameraManager::Instance().Find(kSkyboxCameraName);
  Camera& main_camera = CameraManager::Instance().FindUsingHandle(0);
  D3DXVECTOR3 dir = main_camera.CalculateCameraDirection();
  D3DXVECTOR3 eye(-dir);
  p_camera_steering_->SetAtValue(dir);
  p_camera_steering_->SetEyeValue(eye);

  _DrawChildAll();

  p_device->SetRenderState(D3DRS_LIGHTING, TRUE);
  p_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
  p_device->SetTransform(D3DTS_VIEW, &view_old);
}
