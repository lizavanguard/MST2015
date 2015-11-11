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

#include "Framework/Object/object3d.h"
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Camera/camera_manager.h"
//#include "Framework/Camera/camera_manager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTexturenames[] = {
    //"data/Texture/SkyBox/PurpleValley/purplevalley_bk.tga",	// Z+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_ft.tga",	// Z-
    //"data/Texture/SkyBox/PurpleValley/purplevalley_rt.tga",	// X+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_lf.tga",	// X-
    //"data/Texture/SkyBox/PurpleValley/purplevalley_up.tga",	// Y+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_dn.tga",	// Y-
    "st_bk.tga",	// Z+
    "st_ft.tga",	// Z-
    "st_rt.tga",	// X+
    "st_lf.tga",	// X-
    "st_up.tga",	// Y+
    "st_dn.tga",	// Y-
  };

  const float kSize = 100.0f;
  const float kSizeHalf = kSize / 2.0f;
  const float kSizeOffset = kSizeHalf - 0.5f;

  const D3DXVECTOR3 kPoses[6] = {
    D3DXVECTOR3(0, 0, kSizeOffset),	// Z+
    D3DXVECTOR3(0, 0, -kSizeOffset),	// Z-
    D3DXVECTOR3(kSizeOffset, 0, 0),	// X+
    D3DXVECTOR3(-kSizeOffset, 0, 0),	// X-
    D3DXVECTOR3(0, kSizeOffset, 0),	// Y+
    D3DXVECTOR3(0, -kSizeOffset, 0),	// Y-
  };

  const D3DXVECTOR3 kRots[SkyBox::kNumFaces] = {
    D3DXVECTOR3(0, 0, 0),
    D3DXVECTOR3(0, liza::math::kPIf, 0),
    D3DXVECTOR3(0, -liza::math::kPIHalff, 0),
    D3DXVECTOR3(0, liza::math::kPIHalff, 0),
    D3DXVECTOR3(0, -liza::math::kPIHalff, liza::math::kPIHalff),
    D3DXVECTOR3(0, -liza::math::kPIHalff, -liza::math::kPIHalff),
  };
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SkyBox::SkyBox() {
  for (unsigned int face_count = 0; face_count < kNumFaces; ++face_count) {
    auto object = Object3DFactory::Create(kTexturenames[face_count]);
    object->SetPosition(kPoses[face_count]);
    object->SetRotation(kRots[face_count]);
    AttachChild(object);
  }

  //// UV
  //for (int face_count = 0; face_count < kNumFaces; ++face_count) {
  //  pMeshBoards_[face_count]->ChangeUV(0.0005f, 0.9995f, 0.0005f, 0.9995f);
  //}
}


//------------------------------------------------
// dtor
//------------------------------------------------
SkyBox::~SkyBox() {
}


//------------------------------------------------
// Update
//------------------------------------------------
void SkyBox::_Update(const float elapsed_time) {
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

  Camera& camera = CameraManager::Instance().GetCamera(0);
  D3DXVECTOR3 up(0, 1, 0);
  D3DXVECTOR3 dir = camera.CalculateCameraDirection();
  D3DXVECTOR3 eye(-dir);
  D3DXMATRIX view;
  D3DXMatrixLookAtLH(&view, &eye, &dir, &up);
  p_device->SetTransform(D3DTS_VIEW, &view);

  for (int face_count = 0; face_count < kNumFaces; ++face_count) {
    D3DXMATRIX translation;
    D3DXMatrixTranslation(&translation, kPoses[face_count].x, kPoses[face_count].y, kPoses[face_count].z);
    D3DXMATRIX rotation;
    D3DXMatrixRotationYawPitchRoll(&rotation, kRots[face_count].y, kRots[face_count].x, kRots[face_count].z);
    D3DXMATRIX world = translation * rotation;
    p_device->SetTransform(D3DTS_WORLD, &world);

    //RendererSingleton::Instance().SetTexture(pMeshTexs_[face_count]);
    //pMeshBoards_[face_count]->Draw();
  }

  p_device->SetRenderState(D3DRS_LIGHTING, TRUE);
  p_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
  p_device->SetTransform(D3DTS_VIEW, &view_old);
}