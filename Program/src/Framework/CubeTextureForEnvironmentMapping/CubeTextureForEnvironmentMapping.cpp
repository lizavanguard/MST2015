//==============================================================================
//
// CubeTextureForEnvironmentMapping
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "CubeTextureForEnvironmentMapping.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Utility/DeviceHolder.h"

using cube_mapping::kCubeCamera;
using cube_mapping::kCubeSkyBoxCamera;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const unsigned int kNumFaces = 6;
  const unsigned int kSurfaceSize = 128;

  const D3DXVECTOR3 kLookAtTables[kNumFaces] = {
    D3DXVECTOR3( 1.0f,  0.0f,  0.0f),  // +X
    D3DXVECTOR3(-1.0f,  0.0f,  0.0f),  // -X
    D3DXVECTOR3( 0.0f,  1.0f,  0.0f),  // +Y
    D3DXVECTOR3( 0.0f, -1.0f,  0.0f),  // -Y
    D3DXVECTOR3( 0.0f,  0.0f,  1.0f),  // +Z
    D3DXVECTOR3( 0.0f,  0.0f, -1.0f)   // -Z
  };
  const D3DXVECTOR3 kUpTables[kNumFaces] = {
    D3DXVECTOR3(0.0f, 1.0f,  0.0f),  // +X(Up = +Y)
    D3DXVECTOR3(0.0f, 1.0f,  0.0f),  // -X(Up = +Y)
    D3DXVECTOR3(0.0f, 0.0f, -1.0f),  // +Y(Up = -Z)
    D3DXVECTOR3(0.0f, 0.0f,  1.0f),  // -X(Up = +Z)
    D3DXVECTOR3(0.0f, 1.0f,  0.0f),  // +Z(Up = +Y)
    D3DXVECTOR3(0.0f, 1.0f,  0.0f),  // -Z(Up = +Y)
  };

}
//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
unsigned int CubeTextureForEnvironmentMapping::num_ = 0;

//------------------------------------------------
// ctor
//------------------------------------------------
CubeTextureForEnvironmentMapping::CubeTextureForEnvironmentMapping(ObjectDrawer* p_object_drawer)
    : pp_dynamic_cube_texture_(nullptr)
    , p_object_drawer_(p_object_drawer) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateCubeTexture(kSurfaceSize, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pp_dynamic_cube_texture_, nullptr);

  if (num_ == 0) {
    {  // standard camera
      Camera* p_camera = new Camera(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
      p_camera->OffMatrixAutoUpdate();
      CameraManager::Instance().Register(kCubeCamera, p_camera);
    }

    {  // skybox camera
      Camera* p_camera = new Camera(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
      p_camera->OffMatrixAutoUpdate();
      CameraManager::Instance().Register(kCubeSkyBoxCamera, p_camera);
    }
  }
  ++num_;
}

//------------------------------------------------
// dtor
//------------------------------------------------
CubeTextureForEnvironmentMapping::~CubeTextureForEnvironmentMapping() {
  //--num_;
  SafeDelete(p_object_drawer_);
  SafeRelease(pp_dynamic_cube_texture_);
}

//------------------------------------------------
// Draw
//------------------------------------------------
void CubeTextureForEnvironmentMapping::Draw(const D3DXVECTOR3& position) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_device->EndScene();

  p_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

  D3DVIEWPORT9 OldViewport, Viewport;
  p_device->GetViewport(&OldViewport);
  Viewport.Height = kSurfaceSize;
  Viewport.Width = kSurfaceSize;
  Viewport.MaxZ = 1.0f;
  Viewport.MinZ = 0.0f;
  Viewport.X = 0;
  Viewport.Y = 0;
  p_device->SetViewport(&Viewport);

  auto& camera = CameraManager::Instance().Find(kCubeCamera);
  auto& skybox_camera = CameraManager::Instance().Find(kCubeSkyBoxCamera);

  for (unsigned i = 0; i < kNumFaces; i++) {
    // サーフェイス指定
    IDirect3DSurface9 *renderTarget, *oldTarget;
    pp_dynamic_cube_texture_->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &renderTarget);
    renderTarget->Release();
    p_device->GetRenderTarget(0, &oldTarget);
    oldTarget->Release();
    p_device->SetRenderTarget(0, renderTarget);

    // Direct3Dの処理
    p_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    p_device->BeginScene();
    // ビュー行列を作成
    // position = center of cube
    D3DXMATRIX view;
    D3DXVECTOR3 lookAtPos = kLookAtTables[i] + position;
    D3DXMatrixLookAtLH(&view, &position, &lookAtPos, &kUpTables[i]);
    camera._SetViewMatrix(view);

    D3DXMATRIX skybox_view;
    D3DXMatrixLookAtLH(&skybox_view, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &kLookAtTables[i], &kUpTables[i]);
    skybox_camera._SetViewMatrix(skybox_view);

    // パースペクティブは90度で
    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(90.0f), 1.0f, 1.0f, 10000.0f);
    camera._SetProjectionMatrix(proj);
    skybox_camera._SetProjectionMatrix(proj);

    // オブジェクト描画
    if (p_object_drawer_) {
      p_object_drawer_->_DrawObject();
    }

    p_device->EndScene();

    p_device->SetRenderTarget(0, oldTarget);
  }

  p_device->SetViewport(&OldViewport);

  p_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

  p_device->BeginScene();
}
