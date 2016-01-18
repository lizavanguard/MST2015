//==============================================================================
//
// Pin
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Pin.h"

#include "Application/Game/SceneGame.h"

#include "Framework/Bullet/BulletFactory.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kSize = 90.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Pin::Pin(const D3DXVECTOR3& position, SceneGame* p_scene_game, const char *p_filename)
    : ObjectModel(p_filename)
    , CollisionObject(kSize)
    , initial_position_(position)
    , handle_(BulletManager::NullHandle)
    , p_scene_game_(p_scene_game) {
  position_ = position;

  if (p_scene_game_) {
    handle_ = p_scene_game_->GetBulletManager().Generate(
      new bullet::PillarFactory(D3DXVECTOR3(kSize, pin::lane_pin::kHalfSizeY, kSize)),
      position_,
      0.001f,
      0.75f,
      1.0f);
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
Pin::~Pin() {
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Pin::Reset(void) {
  position_ = initial_position_;
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  is_all_drawed_ = true;
  is_collided_ = false;

  if (handle_ != BulletManager::NullHandle) {
    p_scene_game_->GetBulletManager().SetPosition(handle_, initial_position_);
  }
}


//------------------------------------------------
// Update
//------------------------------------------------
void Pin::_Update(const float elapsed_time) {
  if (handle_ == BulletManager::NullHandle) {
    velocity_ *= 0.998f;
    speed_ += velocity_;
    speed_ *= 0.998f;
    position_ += speed_ * elapsed_time;
  }
  else {
    position_ = p_scene_game_->GetBulletManager().GetPosition(handle_);
    position_.y += 490.803040f / 2;
    rotation_matrix_ = p_scene_game_->GetBulletManager().GetRotationMatrix(handle_);
    rotation_.y = rotation_matrix_._22;
  }
}
