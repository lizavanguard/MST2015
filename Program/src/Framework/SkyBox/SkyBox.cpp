//==============================================================================
//
// スカイボックス [SkyBox.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SkyBox.h"

#include "Framework/Object/object3d.h"

#include "Camera/Camera.h"
#include "Camera/CameraManager.h"
#include "GameManager/GameManager.h"
#include "3D/Mesh/MeshBoard.h"
#include "3D/Renderer/RendererDX.h"
#include "3D/ResourceManager/ResourceManager.h"
#include "3D/Texture/TextureDX.h"


#include "GameManager/GameManager.h"
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kTexnames[SkyBox::kFaceMax] = {
    //"data/Texture/SkyBox/PurpleValley/purplevalley_bk.tga",	// Z+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_ft.tga",	// Z-
    //"data/Texture/SkyBox/PurpleValley/purplevalley_rt.tga",	// X+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_lf.tga",	// X-
    //"data/Texture/SkyBox/PurpleValley/purplevalley_up.tga",	// Y+
    //"data/Texture/SkyBox/PurpleValley/purplevalley_dn.tga",	// Y-
    "data/Texture/SkyBox/St/st_bk.tga",	// Z+
    "data/Texture/SkyBox/St/st_ft.tga",	// Z-
    "data/Texture/SkyBox/St/st_rt.tga",	// X+
    "data/Texture/SkyBox/St/st_lf.tga",	// X-
    "data/Texture/SkyBox/St/st_up.tga",	// Y+
    "data/Texture/SkyBox/St/st_dn.tga",	// Y-
  };

  const float kSize = 100.0f;
  const float kSizeHalf = kSize / 2.0f;
  const float kSizeOffset = kSizeHalf - 0.5f;

  const Vector3 kPoses[SkyBox::kFaceMax] = {
    Vector3(0, 0, kSizeOffset),	// Z+
    Vector3(0, 0, -kSizeOffset),	// Z-
    Vector3(kSizeOffset, 0, 0),	// X+
    Vector3(-kSizeOffset, 0, 0),	// X-
    Vector3(0, kSizeOffset, 0),	// Y+
    Vector3(0, -kSizeOffset, 0),	// Y-
  };

  const Vector3 kRots[SkyBox::kFaceMax] = {
    Vector3(0, 0, 0),
    Vector3(0, liza::math::kPIf, 0),
    Vector3(0, -liza::math::kPIHalff, 0),
    Vector3(0, liza::math::kPIHalff, 0),
    Vector3(0, -liza::math::kPIHalff, liza::math::kPIHalff),
    Vector3(0, -liza::math::kPIHalff, -liza::math::kPIHalff),
  };
}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SkyBox::SkyBox() {
  for (int i = 0; i < kFaceMax; ++i) {
    pMeshBoards_[i] = nullptr;
    pMeshTexs_[i] = nullptr;
  }

  // Create Mesh
  for (int i = 0; i < kFaceMax; ++i) {
    pMeshBoards_[i] = new MeshBoard(kSize, kSize);
  }

  // Load Tex
  for (int i = 0; i < kFaceMax; ++i) {
    pMeshTexs_[i] = ResourceManager::Instance().CreateTextureFromFile(kTexnames[i]);
  }

  // UV
  for (int i = 0; i < kFaceMax; ++i) {
    pMeshBoards_[i]->ChangeUV(0.0005f, 0.9995f, 0.0005f, 0.9995f);
  }
}


//------------------------------------------------
// dtor
//------------------------------------------------
SkyBox::~SkyBox() {
  for (int i = 0; i < kFaceMax; ++i) {
    SafeDelete(pMeshBoards_[i]);
  }
}


//------------------------------------------------
// Update
//------------------------------------------------
void SkyBox::Update(const float elapsedTime) {
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SkyBox::Draw(void) {
  auto& rRenderer = RendererSingleton::Instance();
  LPDIRECT3DDEVICE9 pDevice = rRenderer.GetDevice();

  // 現在のビュー行列を取得
  Matrix mtxViewOld;
  rRenderer.GetTransform(D3DTS_VIEW, &mtxViewOld);

  // Zバッファ書き込みを無効
  rRenderer.SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

  // ライトの無効
  rRenderer.SetRenderState(D3DRS_LIGHTING, FALSE);

  // 新しいビュー行列を設定
  Camera& rCamera = GameManagerSingleton::Instance().GetCameraManager().GetPrimaryCamera();
  Vector3 up(0, 1, 0);
  Vector3 dir(rCamera.GetAt() - rCamera.GetEye());
  dir.Normalize();
  Vector3 eye(-dir);
  Matrix mtxView;
  mtxView.LookAt(eye, dir, up);
  rRenderer.SetTransform(D3DTS_VIEW, mtxView);

  // 六面描画
  for (int i = 0; i < kFaceMax; ++i) {
    Matrix mtxWorld;
    mtxWorld.Transform(kPoses[i], kRots[i], Vector3(1, 1, 1));
    rRenderer.SetTransform(D3DTS_WORLD, mtxWorld);

    RendererSingleton::Instance().SetTexture(pMeshTexs_[i]);
    pMeshBoards_[i]->Draw();
  }

  // ライトを有効
  rRenderer.SetRenderState(D3DRS_LIGHTING, TRUE);

  // Zバッファ書き込みを有効
  rRenderer.SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

  // ビュー行列を戻す
  rRenderer.SetTransform(D3DTS_VIEW, mtxViewOld);
}