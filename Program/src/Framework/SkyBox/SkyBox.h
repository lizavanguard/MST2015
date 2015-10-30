//==============================================================================
//
// スカイボックス [SkyBox.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Framework/Object/object_base.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Object3D;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SkyBox : public ObjectBase {
public:
  // const
  static const int kFaceMax = 6;

public:
  // ctor
  SkyBox();

  // dtor
  ~SkyBox();

  // Update
  void Update(float elapsedTime);

  // Draw
  void Draw(void);

  Vector3 GetRottt(void) const;

private:
  // property
  MeshBoard* pMeshBoards_[kFaceMax];
  TextureDX* pMeshTexs_[kFaceMax];
};


#endif // __H_SKYBOX_H__