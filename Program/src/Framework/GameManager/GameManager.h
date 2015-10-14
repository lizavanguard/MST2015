//==============================================================================
//
// ÉQÅ[ÉÄä«óù [GameManager.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_GAMEMANAGER_H__
#define __H_GAMEMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include "d3dx9.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class DebugProc;
class InputManager;
class Test;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class GameManager {
public:
	// Get Instance
	static GameManager& Instance( HINSTANCE hInstance = nullptr, HWND hWnd = nullptr, LPDIRECT3DDEVICE9 pDevice = nullptr );

private:
	// ctor/dtor/copy/assign
	GameManager( HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 pDevice );
	GameManager( const GameManager& );
	GameManager& operator = ( const GameManager& );
	~GameManager();

public:
	// Update
	void Update( void );
	
	// Draw
	void Draw( void );

	// Get
	LPDIRECT3DDEVICE9 GetDevice( void ) { return pDevice_; }
	DebugProc& GetDebugProc( void ) { return *pDebugProc_; }
	InputManager& GetInputManager( void ) { return *pInputManager_; }

private:
	// property
	LPDIRECT3DDEVICE9 pDevice_;
	DebugProc* pDebugProc_;
	InputManager* pInputManager_;
	Test* pTest_;
};


#endif // __H_GAMEMANAGER_H__