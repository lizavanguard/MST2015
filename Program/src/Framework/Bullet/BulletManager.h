//==============================================================================
//
// BulletManager
// Author: Shimizu Shoji
//
// �����Ɋ�Â����I�u�W�F�N�g�̐����ǉ�
// �I�u�W�F�N�g�ւ̃n���h���̎擾
// �n���h��������e�I�u�W�F�N�g�ւ̃p�����[�^�擾�y�ѐݒ�
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
// Header���Q��
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
  // �`��, ���W, �T�C�Y, ����, �����W��, ���C�W��
  // �߂�l�̓n���h��
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
