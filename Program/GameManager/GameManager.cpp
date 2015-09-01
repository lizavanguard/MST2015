//==============================================================================
//
// ÉQÅ[ÉÄä«óù [GameManager.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameManager.h"
#include "../Input/InputManager.h"
#include "../Input/InputKeyboard.h"
#include "../DebugProc/DebugProc.h"
#include "../Test/Test.h"
#include <liza/SafeDelete.h>


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// Get Instance
//------------------------------------------------
GameManager& GameManager::Instance( HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice ) {
	static GameManager instance( hInstance, hWnd, pDevice );
	return instance;
}


//------------------------------------------------
// ctor
//------------------------------------------------
GameManager::GameManager( HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice )
	: pDevice_( pDevice )
	, pDebugProc_( nullptr )
	, pInputManager_( nullptr )
	, pTest_( nullptr )
{
	pDebugProc_ = new DebugProc();
	pDebugProc_->Init( pDevice_ );
	pInputManager_ = new InputManager( hInstance, hWnd );
	pTest_ = new Test();
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameManager::~GameManager() {
	SafeDelete( pTest_ );
	delete pInputManager_;
	pDebugProc_->Uninit();
	delete pDebugProc_;
}


//------------------------------------------------
// update
//------------------------------------------------
void GameManager::Update( void ) {
	pInputManager_->Update();

	pTest_->Update();
}


//------------------------------------------------
// draw
//------------------------------------------------
void GameManager::Draw( void ) {
	pTest_->Draw();

	pDebugProc_->Draw();
}