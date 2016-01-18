//==============================================================================
//
// BulletManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "BulletManager.h"
#include "BulletUtility.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
BulletManager::BulletManager()
    : p_world_(nullptr)
    , p_config_(nullptr) {
  // �Փˌ��o���@�̑I��(�f�t�H���g��I��)
  p_config_ = new btDefaultCollisionConfiguration();
  btCollisionDispatcher* p_dispatcher = new btCollisionDispatcher(p_config_);
  // �u���[�h�t�F�[�Y�@�̐ݒ�
  btDbvtBroadphase* p_broadphase = new btDbvtBroadphase();  // Dynamic AABB tree method
  // �S��(���̊ԃ����N)�̃\���o�ݒ�
  btSequentialImpulseConstraintSolver* p_solver = new btSequentialImpulseConstraintSolver();

  // Bullet�̃��[���h�쐬
  p_world_ = new btDiscreteDynamicsWorld(p_dispatcher, p_broadphase, p_solver, p_config_);
  // �d�͂̐ݒ�
  p_world_->setGravity(btVector3(0, -9.8f * 1000, 0));

  //delete p_config;
}

//------------------------------------------------
// dtor
//------------------------------------------------
BulletManager::~BulletManager() {
  // �N���A
  Clear();

  // ���[���h�j��
  delete p_world_->getBroadphase();
  delete p_world_->getConstraintSolver();
  delete p_world_->getDispatcher();
  delete p_config_;
  delete p_world_;
}

//------------------------------------------------
// Update
//------------------------------------------------
void BulletManager::Update(const float elapsed_time) {
  //static double dt = 1.0f / 60.0f;
  //btVector3 impulse = btVector3(0, 0, 150); // ���́i�͐ρj
  //btVector3 impulse2 = btVector3(-0.0, 0, 0); // ���́i�͐ρj
  //static btVector3 impulse3 = btVector3(0, 0, 0); // ���́i�͐ρj
  p_world_->stepSimulation(elapsed_time);
  //p_world_->stepSimulation(1.0f / 60.0f);
}

//------------------------------------------------
// Clear
//------------------------------------------------
void BulletManager::Clear(void) {
  for (auto p_object : container_) {
    delete p_object->getMotionState();
    delete p_object->getCollisionShape();
    p_world_->removeRigidBody(p_object);
    delete p_object;
  }
  container_.clear();
}

//------------------------------------------------
// Generate
//------------------------------------------------
BulletManager::Handle BulletManager::Generate(bullet::ShapeFactory* p_shape_factory,
                                                const D3DXVECTOR3& _position,
                                                const float _mass,
                                                const float _restitution,
                                                const float _friction) {
  if (!p_shape_factory) {
    //assert(!"�Ȃɂ��Ȃ���");
    return NullHandle;
  }

  // �����ʒu�Ǝp���̐ݒ�
  btVector3 position = bullet::ToBTVector(_position);
  btQuaternion qrot(0.0f, 0.0f, 0.0f, 1.0f);  // ��{�I�ɃN�H�[�^�j�I���Őݒ肷��
  btDefaultMotionState* p_motion_state = new btDefaultMotionState(btTransform(qrot, position));

  // ���ʂƊ������[�����g�i�C�i�[�V���j�̌v�Z
  btVector3 inertia = btVector3(0.0f, 0.0f, 0.0f);
  btCollisionShape* p_collision_shape = p_shape_factory->Create();
  p_collision_shape->calculateLocalInertia(_mass, inertia);   // inertia�Ɍv�Z���ʂ��㏑�������

  // ���̃I�u�W�F�N�g����(���ʁC�ʒu�p���C�`��C�������[�����g��ݒ�)
  // ���̂̐����ɂ͍Œ���A����4�̈������K�v�ɂȂ�
  btRigidBody* p_object_body = new btRigidBody(_mass, p_motion_state, p_collision_shape, inertia);

  // �����W���̐ݒ�i�f�t�H���g��0�j
  p_object_body->setRestitution(_restitution);
  // �Î~���C�W���̐ݒ�i�f�t�H���g��0.5�j
  p_object_body->setFriction(_friction);
  // ���[���h�ɒǉ�
  p_world_->addRigidBody(p_object_body);
  container_.push_back(p_object_body);

  delete p_shape_factory;
  return container_.size() - 1;
}

BulletManager::Handle BulletManager::Generate(bullet::ShapeFactory* p_shape_factory,
                                                const D3DXVECTOR3& position,
                                                const ObjectGenerationDesc& desc) {
  return Generate(p_shape_factory, position, desc.mass, desc.restitution, desc.friction);
}

//------------------------------------------------
// ApplyImpluse
//------------------------------------------------
void BulletManager::ApplyImpulse(const Handle handle, const D3DXVECTOR3& impulse) {
  auto p_object = container_[handle];
  p_object->applyCentralImpulse(bullet::ToBTVector(impulse * 100));
}

//------------------------------------------------
// get
//------------------------------------------------
D3DXMATRIX BulletManager::GetTransformMatrix(Handle handle) {
  auto p_object = container_[handle];

  btVector3 position = p_object->getCenterOfMassPosition();
  D3DXMATRIX transform;
  D3DXMatrixTranslation(&transform, (float)position[0], (float)position[1], (float)position[2]);

  return transform;
}

D3DXMATRIX BulletManager::GetRotationMatrix(Handle handle) {
  auto p_object = container_[handle];

  btScalar rotation = btScalar(p_object->getOrientation().getAngle());
  btVector3 axis = p_object->getOrientation().getAxis();
  D3DXQUATERNION quaternion_rotation;

  D3DXVECTOR3 vec3axis((float)axis[0], (float)axis[1], (float)axis[2]);
  D3DXQuaternionRotationAxis(&quaternion_rotation, &vec3axis, (float)rotation);
  D3DXMATRIX matrix_rotation;
  D3DXMatrixRotationQuaternion(&matrix_rotation, &quaternion_rotation);

  return matrix_rotation;
}

D3DXVECTOR3 BulletManager::GetPosition(Handle handle) {
  auto p_object = container_[handle];

  btVector3 position = p_object->getCenterOfMassPosition();
  return D3DXVECTOR3((float)position[0], (float)position[1], (float)position[2]);
}

//------------------------------------------------
// set
//------------------------------------------------
void BulletManager::SetPosition(Handle handle, const D3DXVECTOR3& position) {
  auto p_object = container_[handle];
  //p_object->setWorldTransform(transform);

  p_world_->removeRigidBody(p_object);

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(bullet::ToBTVector(position));
  p_object->setWorldTransform(transform);
  p_object->getMotionState()->setWorldTransform(transform);
  p_object->clearForces();
  btVector3 zero(0.0f, 0.0f, 0.0f);
  p_object->setCenterOfMassTransform(transform);
  p_object->setLinearVelocity(zero);
  p_object->setAngularVelocity(zero);
  //p_object->translate(bullet::ToBTVector(position));
  p_object->activate(true);

  p_world_->addRigidBody(p_object);
}

void BulletManager::SetAngularVelocity(Handle handle, const D3DXVECTOR3& velocity) {
  auto p_object = container_[handle];
  p_object->setAngularVelocity(bullet::ToBTVector(velocity));
}

void BulletManager::SetAngularFactor(Handle handle, const float factor) {
  auto p_object = container_[handle];
  p_object->setAngularFactor(factor);
}
