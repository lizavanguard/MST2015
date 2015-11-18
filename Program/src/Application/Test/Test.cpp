//==============================================================================
//
// Test‰ïê [Test.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Test.h"

#include "Framework/Camera/camera_manager.h"
#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"
#include "Framework/Camera/camera_steering_control.h"
#include "Framework/Light/light.h"
#include "Framework/Object/root.h"
#include "Framework/Object/debug_object.h"
#include "Framework/Object/object3d.h"
#include "Framework/Object/object2d.h"
#include "Framework/Object/object_model.h"
#include "Framework/SkyBox/SkyBox.h"
#include "Framework/Sound/sound_manager.h"

#include "Application/Collision/CollisionManager.h"
#include "Application/Pin/PinManager.h"
#include "Application/Player/Player.h"

#include "Application/Controller/Controller.h"


Root* g_p_root = nullptr;
CollisionManager* g_p_collision = nullptr;
Player* player = nullptr;
Controller* p_controller = nullptr;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Test::Test() {
  // camera
  static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 75.0f, -40.0f};
  //static const D3DXVECTOR3 kInitialEyePosition = {0.0f, 10.0f, -40.0f};
  auto camera = CameraFactory::Create(kInitialEyePosition, D3DXVECTOR3(0, 0, 0));
  CameraManager::Instance().Register("MAIN_CAMERA", camera);

  // root
  g_p_root = RootFactory::Create();

  // skybox
  g_p_root->AttachChild(SkyBoxFactory::Create());

  // field
  g_p_root->AttachChild(ObjectModelFactory::Create("field"));

  // player
  player = PlayerFactory::Create();
  g_p_root->AttachChild(player);

  // pin
  auto pin_manager = PinManagerFactory::Create();
  g_p_root->AttachChild(pin_manager);

  // 2D
  auto obj2d = Object2DFactory::Create("field");
  obj2d->SetPosition(D3DXVECTOR3(640, 360, 0));
  g_p_root->AttachChild(obj2d);

  // collision
  g_p_collision = new CollisionManager(*player, *pin_manager);

  // sound
  //SoundManager::Instance().PlaySound(SOUND_LABEL_BGM1);

  //camera->AssignCameraSteering(new CameraSteeringFixed(*player));
  camera->AssignCameraSteering(new CameraSteeringHoming(*player));

  p_controller = new Controller(*player);
}


//------------------------------------------------
// dtor
//------------------------------------------------
Test::~Test() {
  SafeDelete(p_controller);
  CameraManager::Instance().UnRegister();
  SafeDelete(g_p_collision);
  Root::Destroy(g_p_root);
}


//------------------------------------------------
// Update
//------------------------------------------------
void Test::Update( void ) {
  if (GameManager::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_1)) {
    SoundManager::Instance().PlaySound("SE/se000");
  }
  p_controller->Update();

  g_p_root->UpdateAll(0.016f);

  g_p_collision->Update();
}


//------------------------------------------------
// Draw
//------------------------------------------------
void Test::Draw( void ) {
  g_p_root->DrawAll();
}