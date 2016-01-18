//==============================================================================
//
// Player
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Player.h"
#include "PlayerBall.h"

#include "Framework/Object/object_fbx_model.h"
#include "Framework/Bullet/BulletManager.h"

#include "Application/Game/SceneGame.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  const float kScale = 1.00f;
  const float kSize = 190.0f * kScale;

  const float kMovingSpeed = 60.0f;
  const float kMovingControlSpeed = 20.0f;

  const float kAdjustedValueRotationToPower = 200.0f;
  //const float kCurveReaction = 0.025f;
  const float kCurveReaction = 0.011f;
  const float kShotSpeed = 5000.0f;

  const float kSpeedMax = 5000.0f;
  const float kSpeedMaxX = 1000.0f;

  const Vector3 kStartPosition(100.0f, 190.0f * kScale, -6000.0f);

  const float kLimitRotation = 1.5f;
  const float kCurveMax = D3DXToRadian(30.0f);  // 45�x
  const float kCurvePower = 7.5f;
  const float kCurveImpulsePower = 0.04f;
  const float kForwardPower = 25.0f;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Player::Player(CubeTextureForEnvironmentMapping::ObjectDrawer* p_object_drawer, SceneGame* p_scene_game)
    : CollisionObject(kSize)
    , is_shot_(false)
    , adjusted_value_(kAdjustedValueRotationToPower)
    , curve_reaction_(kCurveReaction)
    , shot_speed_(kShotSpeed)
    , moving_speed_(kMovingSpeed)
    , control_speed_(0.0f)
    , shoot_position_(0.0f, 0.0f, 0.0f)
    , shoot_rotation_(0.0f)
    , p_ball_(nullptr)
    , h_wind_effect_(-1)
    , h_fire_effect_(-1)
    , p_scene_game_(p_scene_game)
    , handle_(BulletManager::NullHandle)
    , shot_impulse_(0.0f) {
  this->SetScale(D3DXVECTOR3(kScale, kScale, kScale));
  auto human = new ObjectFBXModel("humanG_07.fbx");
  human->SetPosition(D3DXVECTOR3(0.0f, -75.0f, -125.0f));
  human->SetScale(D3DXVECTOR3(kScale, kScale, kScale));
  AttachChild(human);
  auto ball_obj = new ObjectModel("ballObj_03");
  ball_obj->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
  //ball_obj->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
  AttachChild(ball_obj);
  p_ball_ = new PlayerBall(p_object_drawer);
  AttachChild(p_ball_);
  Reset();

  if (p_scene_game_) {
    handle_ = p_scene_game_->GetBulletManager().Generate(new bullet::SphereFactory(this->GetSize()), kStartPosition,
      0.17f, 0.8f, 0.7f);
    p_scene_game_->GetBulletManager().SetAngularVelocity(handle_, D3DXVECTOR3(-.1f, 0, 0));
    p_ball_->OnSetRotationMatrix();
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
Player::~Player() {
  EffectManagerServiceLocator::Get()->Stop3D(h_fire_effect_);
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);
}

//------------------------------------------------
// Move
//------------------------------------------------
void Player::MoveForward(void) {
  speed_.z += moving_speed_;
}

void Player::MoveForward(const float speed) {
  speed_.z = speed;
}

void Player::MoveBackward(void) {
  speed_.z -= moving_speed_;
}

void Player::MoveLeft(void) {
  control_speed_ -= kMovingControlSpeed;
}

void Player::MoveRight(void) {
  control_speed_ += kMovingControlSpeed;
}

void Player::MoveUp(void) {
  speed_.y += kMovingControlSpeed;
}

void Player::MoveDown(void) {
  speed_.y -= kMovingControlSpeed;
}

void Player::MoveStop(void) {
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  EffectManagerServiceLocator::Get()->Stop3D(h_fire_effect_);
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);
}

//------------------------------------------------
// Shoot
//------------------------------------------------
void Player::Shoot(const float rotation) {
  if (is_shot_) {
    return;
  }

  speed_.z += shot_speed_;

  const float true_power = -rotation * adjusted_value_;
  speed_.x = true_power;
  velocity_.x -= true_power * curve_reaction_;

  p_ball_->Shoot(rotation);

  is_shot_ = true;

  h_wind_effect_ = EffectManagerServiceLocator::Get()->Play3D("EF_Game_ballWind", position_.x, position_.y, position_.z + 300);
  EffectManagerServiceLocator::Get()->SetRotation(h_wind_effect_, D3DXVECTOR3(0, 1, 0), D3DX_PI);
  EffectManagerServiceLocator::Get()->SetScale(h_wind_effect_, 100, 100, 100);

  h_fire_effect_ = EffectManagerServiceLocator::Get()->Play3D("EF_Game_ballFire", position_.x, position_.y - 175, position_.z + 200);
  EffectManagerServiceLocator::Get()->SetRotation(h_fire_effect_, D3DXVECTOR3(0, 1, 0), D3DX_PI);
  EffectManagerServiceLocator::Get()->SetScale(h_fire_effect_, 100, 100, 100);

  shoot_position_ = position_;
  shoot_rotation_ = rotation;

  if (handle_ != BulletManager::NullHandle) {
    // ���E��]�l�ɃN�����v / ���E��]�l => -1 ~ 1
    const float calc_rotation = liza::math::Clamp(rotation, kLimitRotation) / kLimitRotation;

    D3DXVECTOR3 forward(
      sinf(calc_rotation * kCurveMax) * kCurvePower,
      0.0f,
      cosf(calc_rotation * kCurveMax) * kForwardPower);

    p_scene_game_->GetBulletManager().ApplyImpulse(handle_, forward);

    shot_impulse_ = kCurveImpulsePower * -calc_rotation;
  }
}

//------------------------------------------------
// Brake
//------------------------------------------------
void Player::Brake(void) {
  if (handle_ != BulletManager::NullHandle) {
    p_scene_game_->GetBulletManager().ApplyImpulse(handle_, D3DXVECTOR3(0, 0, -0.2f));
  }
}

//------------------------------------------------
// Reset
//------------------------------------------------
void Player::Reset(void) {
  EffectManagerServiceLocator::Get()->Stop3D(h_fire_effect_);
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);

  is_shot_ = false;
  position_ = kStartPosition;
  rotation_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  p_ball_->Reset();

  if (handle_ != BulletManager::NullHandle) {
    p_scene_game_->GetBulletManager().SetPosition(handle_, kStartPosition);
    p_scene_game_->GetBulletManager().SetAngularVelocity(handle_, D3DXVECTOR3(-.1f, 0, 0));
  }
}

//------------------------------------------------
// React collision
//------------------------------------------------
void Player::ReactCollision(const D3DXVECTOR3&) {
  // �ύX�_
  velocity_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  speed_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  EffectManagerServiceLocator::Get()->Stop3D(h_wind_effect_);
  EffectManagerServiceLocator::Get()->Stop3D(h_fire_effect_);
  // end
  return;
}

//------------------------------------------------
// Update
//------------------------------------------------
void Player::_Update(const float elapsed_time) {
#ifdef _DEBUG
  auto& keyboard = GameManager::Instance().GetInputManager().GetPrimaryKeyboard();
  static const float kSpeed = 100.0f;
  const float true_speed = kSpeed /** elapsed_time*/;

  if (keyboard.IsPress(DIK_3)) { curve_reaction_+= 0.0003f; }
  if (keyboard.IsPress(DIK_4)) { curve_reaction_ -= 0.0003f; }
  if (keyboard.IsPress(DIK_5)) { shot_speed_ += 0.1f; }
  if (keyboard.IsPress(DIK_6)) { shot_speed_ -= 0.1f; }
  if (keyboard.IsPress(DIK_7)) { adjusted_value_ += 0.1f; }
  if (keyboard.IsPress(DIK_8)) { adjusted_value_ -= 0.1f; }

  DebugProc::Print("�Ȃ����:[%.3f]\n�ˏo��:[%.3f]\n�Ȃ�����̒����l:[%.3f]\n", curve_reaction_, shot_speed_, adjusted_value_);

#endif

  if (!is_shot_) {
    velocity_.x *= 0.99f;
    speed_ += velocity_;
    if (speed_.z > kSpeedMax) {
      speed_.z = kSpeedMax;
    }

    control_speed_ = liza::math::Clamp(control_speed_, kSpeedMaxX);
    control_speed_ *= 0.7f;
    position_.x += control_speed_;

    //speed_ *= 0.998f;
    position_ += speed_ * elapsed_time;

    static const float kRotationFixedValue = 0.001f;
    p_ball_->AddRotationPower(speed_.z * elapsed_time * kRotationFixedValue);

    if (handle_ != BulletManager::NullHandle) {
      p_scene_game_->GetBulletManager().SetPosition(handle_, position_);
    }
  }
  else {  // is_shot_
    if (handle_ != BulletManager::NullHandle) {
      auto& bullet_manager = p_scene_game_->GetBulletManager();
      position_ = bullet_manager.GetPosition(handle_);
      bullet_manager.ApplyImpulse(handle_, D3DXVECTOR3(shot_impulse_, 0.0f, 0.0f));
      p_ball_->SetRotationMatrix(p_scene_game_->GetBulletManager().GetRotationMatrix(handle_));
    }
  }

  EffectManagerServiceLocator::Get()->SetPosition(h_wind_effect_, position_.x, position_.y, position_.z + 300);
  EffectManagerServiceLocator::Get()->SetPosition(h_fire_effect_, position_.x, position_.y - 175, position_.z + 200);
}

//------------------------------------------------
// set
//------------------------------------------------
void Player::ChangeDrawingOuterFace(const bool is_drawn_outer_face) {
  p_ball_->ChangeDrawingOuterFace(is_drawn_outer_face);
}

//------------------------------------------------
// Draw
// BeginScene��EndScene�̊ԂŌĂяo����
//------------------------------------------------
void Player::UpdateCubeMapping(void) {
  p_ball_->UpdateCubeMapping();
}
