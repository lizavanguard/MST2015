//==============================================================================
//
// BulletFactory
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace bullet {

// ファクトリ
class ShapeFactory {
public:
  // dtor
  virtual ~ShapeFactory() {}

  // Create
  virtual btCollisionShape* Create(void) = 0;
};

// 球状オブジェクトファクトリ
class SphereFactory : public ShapeFactory {
public:
  // ctor/dtor
  SphereFactory(float r) : r_(r) {}
  virtual ~SphereFactory() {}

  // Create
  virtual btCollisionShape* Create(void) {
    return new btSphereShape(r_);
  }

private:
  // property
  float r_;
};

// 柱状オブジェクトファクトリ
class PillarFactory : public ShapeFactory {
public:
  // ctor/dtor
  PillarFactory(const D3DXVECTOR3& size) : size_(size) {}
  PillarFactory(float x, float y, float z) : size_(x, y, z) {}
  virtual ~PillarFactory() {}

  // Create
  virtual btCollisionShape* Create(void) {
    return new btBoxShape(btVector3(size_.x * 0.5f, size_.y * 0.5f, size_.z * 0.5f));
  }

private:
  // property
  D3DXVECTOR3 size_;
};

// 箱状オブジェクトファクトリ
class BoxFactory : public ShapeFactory {
public:
  // ctor/dtor
  BoxFactory(const D3DXVECTOR3& size) : size_(size) {}
  BoxFactory(float x, float y, float z) : size_(x, y, z) {}
  virtual ~BoxFactory() {}

  // Create
  virtual btCollisionShape* Create(void) {
    return new btBoxShape(btVector3(size_.x * 0.5f, size_.y * 0.5f, size_.z * 0.5f));
  }

private:
  // property
  D3DXVECTOR3 size_;
};

}  // namespace bullet
