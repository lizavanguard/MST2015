//==============================================================================
//
// Test2
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Test2.h"

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
// 描画管理インスタンスの生成
::EffekseerRenderer::Renderer* renderer;
// エフェクト管理用インスタンスの生成
::Effekseer::Manager* manager;

// エフェクトの読込
Effekseer::Effect* effect;
// エフェクトの再生
Effekseer::Handle handle;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Test2::Test2() {
  // 描画管理インスタンスの生成
  renderer = ::EffekseerRendererDX9::Renderer::Create(DeviceHolder::Instance().GetDevice(), 2000);
  // エフェクト管理用インスタンスの生成
  manager = ::Effekseer::Manager::Create(2000);

  // 描画方法の指定、独自に拡張しない限り定形文です。
  manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
  manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
  manager->SetRingRenderer(renderer->CreateRingRenderer());
  // テクスチャ画像の読込方法の指定(パッケージ等から読み込む場合拡張する必要があります。)
  manager->SetTextureLoader(renderer->CreateTextureLoader());
  // 座標系の指定(RHで右手系、LHで左手系)
  //manager->SetCoordinateSystem(::Effekseer::COORDINATE_SYSTEM_RH);

  // エフェクトの読込
  effect = Effekseer::Effect::Create(manager, (const EFK_CHAR*)(L"data/Effect/b_square.efk"));
  // エフェクトの再生
  handle = manager->Play(effect,0,0,0);
}

//------------------------------------------------
// dtor
//------------------------------------------------
Test2::~Test2() {
  // エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
  ES_SAFE_RELEASE(effect);
  // エフェクト管理用インスタンスを破棄
  manager->Destroy();
  // 描画用インスタンスを破棄
  renderer->Destory();
}

void Test2::Update() {
  //auto& camera = CameraManager::Instance().Find("MAIN_CAMERA");
  //const auto& proj = camera.GetProjectionMatrix();
  //const auto& view = camera.GetViewMatrix();
  //Effekseer::Matrix44 efk_view;
  //Effekseer::Matrix44 efk_proj;
  //for(int i = 0; i < 4; ++i) {
  //  for( int j = 0; j < 4; ++j ) {
  //    efk_view.Values[i][j] = view.m[i][j];
  //    efk_proj.Values[i][j] = proj.m[i][j];
  //  }
  //}

  //// 投影行列の更新
  //renderer->SetProjectionMatrix(efk_proj);
  //// カメラ行列の更新
  //renderer->SetCameraMatrix(efk_view);
  //// 3Dサウンド用リスナー設定の更新
  ////sound->SetListener(リスナー位置, 注目点, 上方向ベクトル);
  //// 再生中のエフェクトの移動等(::Effekseer::Manager経由で様々なパラメーターが設定できます。)
  ////manager->AddLocation(handle, ::Effekseer::Vector3D);
  //// 全てのエフェクトの更新
  //manager->Update();
}

void Test2::Draw() {
  renderer->BeginRendering();
  manager->Draw();
  renderer->EndRendering();
}