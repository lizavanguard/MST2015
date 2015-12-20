//==============================================================================
//
// �Q�[���Ǘ� [GameManager.h]
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

//#include "Framework/Effect/EffectManager.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class AlphaObjectManager;
class DebugProc;
class EffectManager;
class GameSpeedManager;
class HudManager;
class InputManager;
class SceneManager;
class ScoreHolder;
class Light;

namespace post_effect {
  class PostEffectManager;
}

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
	void Update( float elpasedTime );
	
	// Draw
	void Draw( void );

	// Get
	DebugProc& GetDebugProc( void ) { return *pDebugProc_; }
	InputManager& GetInputManager( void ) { return *pInputManager_; }

private:
	// property
  AlphaObjectManager* pAlphaObjectManager_;
	DebugProc* pDebugProc_;
  EffectManager* pEffectManager_;
  GameSpeedManager* pGameSpeedManager_;
  HudManager* pHudManager_;
	InputManager* pInputManager_;
  SceneManager* pSceneManager_;
  ScoreHolder* pScoreHolder_;
  Light* pLight_;

  post_effect::PostEffectManager* pPostEffectManager_;
};


#endif // __H_GAMEMANAGER_H__