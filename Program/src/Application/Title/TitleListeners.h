//==============================================================================
//
// TitleListeners
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Alarm/Alarm.h"
#include "Application/Player/Player.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Hud/HudManager.h"
#include "Framework/Object/object2d.h"
#include "Framework/Steering/Object2D/Object2DSteeringFlashing.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class PlayerStartListener : public Alarm::Listener {
public:
  // ctor/dtor
  PlayerStartListener(Player& player) : player_(player) {}
  virtual ~PlayerStartListener() {}

  // Notify
  virtual void Notify(void) override {
    CameraManager::Instance().Find("MAIN_2").AssignCameraSteering(new CameraSteeringFixed(player_));
  }

private:
  Player& player_;
};

class SideViewListener : public Alarm::Listener {
public:
  // ctor/dtor
  SideViewListener() {}
  virtual ~SideViewListener() {}

  // Notify
  virtual void Notify(void) override {
    CameraManager::Instance().SetMainCameraUsingHandle(2);
  }
};

class AudienceViewListener : public Alarm::Listener {
public:
// ctor/dtor
  AudienceViewListener(Player& player) : player_(player) {}
  virtual ~AudienceViewListener() {}

  // Notify
  virtual void Notify(void) override {
    auto& camera = CameraManager::Instance().Find("MAIN_2");
    camera._SetEye(D3DXVECTOR3(1000, 1000, 40000));
    camera.AssignCameraSteering(new CameraSteeringFixed(player_));
    CameraManager::Instance().SetMainCameraUsingHandle(1);
  }

private:
  Player& player_;
};

class HomingViewListener : public Alarm::Listener {
public:
  // ctor/dtor
  HomingViewListener(Player& player) : player_(player) {}
  virtual ~HomingViewListener() {}

  // Notify
  virtual void Notify(void) override {
    auto& camera = CameraManager::Instance().Find("MAIN_3");
    camera.AssignCameraSteering(new CameraSteeringHoming(player_, 500.0f, 300.0f, 500.0f));
    CameraManager::Instance().SetMainCameraUsingHandle(2);
  }

private:
  Player& player_;
};

class ImpactListener : public Alarm::Listener {
public:
  // ctor/dtor
  ImpactListener() {}
  virtual ~ImpactListener() {}

  // Notify
  virtual void Notify(void) override {
    auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Title_fadeWhite", 640, 360);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 100, 100);
  }
};

class DummyEndListener : public Alarm::Listener {
public:
  // ctor/dtor
  DummyEndListener() {}
  virtual ~DummyEndListener() {}

  // Notify
  virtual void Notify(void) override {
    auto h = EffectManagerServiceLocator::Get()->Play2D("EF_Title_logoSlideIn", 640, 200);
    EffectManagerServiceLocator::Get()->SetScreenScale(h, 75, 60);

    auto& camera = CameraManager::Instance().FindUsingHandle(1);
    camera._SetEye(D3DXVECTOR3(3000, 3000, 3000));
    camera._SetAt(D3DXVECTOR3(0, 0, 0));
    camera.AssignCameraSteering(nullptr);
    CameraManager::Instance().SetMainCameraUsingHandle(1);

    auto push_start = new Object2D("Title/EF_title_pushSign", D3DXVECTOR3(640, 550, 0), D3DXVECTOR2(500, 150), new Object2DSteeringFlashing(2.0f));
    HudServiceLocator::Get()->PushAlphaHud(push_start);
  }
};
