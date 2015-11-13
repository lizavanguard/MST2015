//==============================================================================
//
// Scene Base [Scene.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_SCENE_H__
#define __H_SCENE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class SceneManager;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Scene {
public:
  // dtor
  virtual ~Scene() {}

private:
  // Update
  virtual void _Update(SceneManager* pSceneManager, float elapsedTime) = 0;

  // Draw
  virtual void _Draw(void) = 0;

  friend SceneManager;
};


#endif // __H_SCENE_H__