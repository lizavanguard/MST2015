//==============================================================================
//
// ReplayListeners
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Alarm/Alarm.h"
#include "Application/Game/SceneGame.h"
#include "Application/Game/GameMaster/GameMaster.h"
#include "Application/Player/Player.h"
#include "Application/Pin/PinManager.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ResetListener : public Alarm::Listener {
public:
  // ctor/dtor
  ResetListener(SceneGame& scene_game, Player& player, PinManager& pin_manager) : scene_game_(scene_game), player_(player), pin_manager_(pin_manager) {}
  virtual ~ResetListener() {}

  // Notify
  virtual void Notify(void) override {
    scene_game_.Reset();
    // camera setting
    auto& player = player_;
    auto& camera_manager = CameraManager::Instance();
    auto& camera1 = camera_manager.Find("MAIN_1");
    camera1.AssignCameraSteering(new CameraSteeringHoming(player, 300, 300, 500));
    auto& camera2 = camera_manager.Find("MAIN_2");
    camera2._SetEye(D3DXVECTOR3(1000, 1000, 10000));
    camera2.AssignCameraSteering(new CameraSteeringFixed(player));
    auto& camera3 = camera_manager.Find("MAIN_3");
    camera3._SetEye(D3DXVECTOR3(-1000, 1000, 30000));
    camera3.AssignCameraSteering(new CameraSteeringFixed(player));

    player_.SetPosition(player_.GetShootPosition());
    pin_manager_.UpdateAll(scene_game_.GetGameMaster().GetShootTime());
    pin_manager_.OffAllUpdated();
  }

private:
  Player& player_;
  PinManager& pin_manager_;
  SceneGame& scene_game_;
};

class ShootListener : public Alarm::Listener {
public:
  // ctor/dtor
  ShootListener(Player& player, PinManager& pin_manager, GameMaster& game_master)
       : player_(player), pin_manager_(pin_manager), game_master_(game_master) {
  }
  virtual ~ShootListener() {}

  // Notify
  virtual void Notify(void) override {
    player_.SetPosition(player_.GetShootPosition());
    player_.Shoot(player_.GetShootRotation());
    pin_manager_.Reset();
    float time = game_master_.GetShootTime();
    pin_manager_.OnAllUpdated();
    pin_manager_.UpdateAll(time);
  }

private:
  Player& player_;
  PinManager& pin_manager_;
  GameMaster& game_master_;
};

class FadeOutListener : public Alarm::Listener {
public:
  // ctor/dtor
  FadeOutListener() {}
  virtual ~FadeOutListener() {}

  // Notify
  virtual void Notify(void) override {
    auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Game_blackOut", 640, 360);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);
  }
};
