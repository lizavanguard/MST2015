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
#include "Framework/Object/root.h"
#include "Framework/Object/debug_object.h"
#include "Framework/Object/object3d.h"
#include "Framework/Light/light.h"
#include "Framework/Object/object_model.h"

Root* g_p_root = nullptr;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Test::Test() {
  g_p_root = Root::Create();
  g_p_root->AttachChild(DebugObject::Create("ID-1"));
  g_p_root->AttachChild(DebugObject::Create("ID-3"));
  g_p_root->AttachChild(DebugObject::Create("ID-5"));

  DebugObject* p_debug_2 = DebugObject::Create("ID-2");
  g_p_root->AttachChild(p_debug_2);
  p_debug_2->AttachChild(Root::Create());
  p_debug_2->AttachChild(DebugObject::Create("ID-4"));
  Root* p_root2 = Root::Create();
  p_debug_2->AttachChild(p_root2);

  Object3D* p_test = Object3D::Create("General/texture001");
  ObjectModel* p_model = ObjectModel::Create("data/Model/car000.x");
  g_p_root->AttachChild(p_test);
  p_test->AttachChild(p_model);
  p_test->AttachChild(Object3D::Create("Game/texture002"));
}


//------------------------------------------------
// dtor
//------------------------------------------------
Test::~Test() {
  Root::Destroy(g_p_root);
}


//------------------------------------------------
// Update
//------------------------------------------------
void Test::Update( void ) {
  g_p_root->UpdateAll(0.016f);
}


//------------------------------------------------
// Draw
//------------------------------------------------
void Test::Draw( void ) {
  g_p_root->DrawAll();
}