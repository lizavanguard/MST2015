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
#include "Framework/Bullet/BulletManager.h"

#include "Application/Game/SceneGame.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const char* kModelName = "stage_09_1220";
  const int kConnectionMax = 1;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Stage::Stage(SceneGame* p_scene_game) : p_scene_game_(p_scene_game), handle_(BulletManager::NullHandle) {
  const float kStageOffset = 35000.0f;
  for (int i = 0; i < kConnectionMax; ++i) {
    auto stage = new ObjectModel(kModelName);
    stage->SetPosition(D3DXVECTOR3(0.0f, 0.0f, kStageOffset * i));
    AttachChild(stage);
  }

  if (p_scene_game_) {
    BulletManager::ObjectGenerationDesc desc;
    desc.mass = 0.0f;
    desc.restitution = 0.8f;
    // 地面
    // 21500
    handle_ = p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(10000.0f, 100.0f, 43000.0f)),
      D3DXVECTOR3(0.0f, -50.0f, 0.0f),
      desc);

    // 右壁
    p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(100.0f, 1500.0f, 70000.0f)),
      D3DXVECTOR3(2000.0f, -100.0f, 0.0f),
      desc);

    // 左壁
    p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(100.0f, 1500.0f, 70000.0f)),
      D3DXVECTOR3(-2000.0f, -100.0f, 0.0f),
      desc);

    // Zゾーン
    // 10000
    handle_ = p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(10000.0f, 100.0f, 20000.0f)),
      D3DXVECTOR3(0.0f, -60.0f, (43000.0f/2)+(20000/2)),
      0.0f, 0.8f, 10000000.0f);

    // Z右壁
    p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(100.0f, 1500.0f, 20000.0f)),
      D3DXVECTOR3(2000.0f, -100.0f, (43000.0f / 2) + (20000 / 2)),
      desc);

    // Z左壁
    p_scene_game_->GetBulletManager().Generate(
      new bullet::BoxFactory(D3DXVECTOR3(100.0f, 1500.0f, 20000.0f)),
      D3DXVECTOR3(-2000.0f, -100.0f, (43000.0f / 2) + (20000 / 2)),
      desc);
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
