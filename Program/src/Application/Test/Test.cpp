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
#include "Framework/Object/root.h"
#include "Framework/Object/debug_object.h"
#include "Framework/Object/object3d.h"
#include "Framework/Light/light.h"
#include "Framework/Object/object_model.h"
#include "Framework/Sound/sound_manager.h"

#include "Application/Collision/CollisionManager.h"
#include "Application/Pin/PinManager.h"
#include "Application/Player/Player.h"

#include "Framework/Camera/camera_steering_fixed.h"
#include "Framework/Camera/camera_steering_homing.h"

Root* g_p_root = nullptr;
CollisionManager* g_p_collision = nullptr;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Test::Test() {
  g_p_root = RootFactory::Create();

  // field
  g_p_root->AttachChild(ObjectModelFactory::Create("field"));

  // player
  auto player = PlayerFactory::Create();
  g_p_root->AttachChild(player);

  auto pin_manager = PinManagerFactory::Create();
  g_p_root->AttachChild(pin_manager);

  CameraManager::Instance().GetCamera(0).AssignCameraSteering(new CameraSteeringFixed(CameraManager::Instance().GetCamera(0), *player));

  //g_p_root->AttachChild(DebugObject::Create("ID-1"));
  //g_p_root->AttachChild(DebugObject::Create("ID-3"));
  //g_p_root->AttachChild(DebugObject::Create("ID-5"));

  //DebugObject* p_debug_2 = DebugObject::Create("ID-2");
  //g_p_root->AttachChild(p_debug_2);
  //p_debug_2->AttachChild(Root::Create());
  //p_debug_2->AttachChild(DebugObject::Create("ID-4"));
  //Root* p_root2 = Root::Create();
  //p_debug_2->AttachChild(p_root2);

  //Object3D* p_test = Object3D::Create("General/texture001");
  //ObjectModel* p_model = ObjectModel::Create("kuma");
  //g_p_root->AttachChild(p_test);
  //p_test->AttachChild(p_model);
  //p_test->AttachChild(Object3D::Create("Model/bear_001"));

  //SoundManager::Instance().PlaySound(SOUND_LABEL_BGM1);
  g_p_collision = new CollisionManager(*player, *pin_manager);
}


//------------------------------------------------
// dtor
//------------------------------------------------
Test::~Test() {
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
  g_p_root->UpdateAll(0.016f);

  g_p_collision->Update();
}


//------------------------------------------------
// Draw
//------------------------------------------------
void Test::Draw( void ) {
  g_p_root->DrawAll();
}