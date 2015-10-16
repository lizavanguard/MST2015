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
}