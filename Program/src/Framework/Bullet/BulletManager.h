//==============================================================================
//
// BulletManager
// Author: Shimizu Shoji
//
// 物理に基づいたオブジェクトの生成追加
// オブジェクトへのハンドルの取得
// ハンドルを介した各オブジェクトへのパラメータ取得及び設定
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "BulletFactory.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// Headerを参照
class BulletManager {
public:
  // alias
  using DataType = btRigidBody*;
  using ContainerType = std::vector<DataType>;

  using Handle = int;

  // const
  static const Handle NullHandle = -1;

  // struct
  struct ObjectGenerationDesc {
    ObjectGenerationDesc() : mass(1.0f), restitution(0.0f), friction(0.5f) {}
    ObjectGenerationDesc(float _mass, float _restitution, float _friction)
        : mass(_mass), restitution(_restitution), friction(_friction) {
    }

    float mass;
    float restitution;
    float friction;
  };

public:
  // ctor
  BulletManager();

  // dtor
  ~BulletManager();

  // Update
  void Update(float elapsed_time);

  // Clear
  void Clear(void);

  // Generate
  // 形状, 座標, サイズ, 質量, 反発係数, 摩擦係数
  // 戻り値はハンドル
  int Generate(bullet::ShapeFactory* p_shape_factory,
               const D3DXVECTOR3& position,
               float mass,
               float restitution,
               float friction);
  int Generate(bullet::ShapeFactory* p_shape_factory,
               const D3DXVECTOR3& position,
               const ObjectGenerationDesc& desc);

  // ApplyImpluse
  void ApplyImpulse(Handle handle, const D3DXVECTOR3& impulse);

  // get
  D3DXMATRIX GetTransformMatrix(Handle handle);
  D3DXMATRIX GetRotationMatrix(Handle handle);
  D3DXVECTOR3 GetPosition(Handle handle);

  // set
  void SetPosition(Handle handle, const D3DXVECTOR3& position);
  void SetAngularVelocity(Handle handle, const D3DXVECTOR3& velocity);
  void SetAngularFactor(Handle handle, float factor);

private:
  // property
  btDynamicsWorld* p_world_;
  btDefaultCollisionConfiguration* p_config_;
  ContainerType container_;
};
