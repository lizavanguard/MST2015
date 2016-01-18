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
  // 衝突検出方法の選択(デフォルトを選択)
  p_config_ = new btDefaultCollisionConfiguration();
  btCollisionDispatcher* p_dispatcher = new btCollisionDispatcher(p_config_);
  // ブロードフェーズ法の設定
  btDbvtBroadphase* p_broadphase = new btDbvtBroadphase();  // Dynamic AABB tree method
  // 拘束(剛体間リンク)のソルバ設定
  btSequentialImpulseConstraintSolver* p_solver = new btSequentialImpulseConstraintSolver();

  // Bulletのワールド作成
  p_world_ = new btDiscreteDynamicsWorld(p_dispatcher, p_broadphase, p_solver, p_config_);
  // 重力の設定
  p_world_->setGravity(btVector3(0, -9.8f * 1000, 0));

  //delete p_config;
}

//------------------------------------------------
// dtor
//------------------------------------------------
BulletManager::~BulletManager() {
  // クリア
  Clear();

  // ワールド破棄
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
  //btVector3 impulse = btVector3(0, 0, 150); // 撃力（力積）
  //btVector3 impulse2 = btVector3(-0.0, 0, 0); // 撃力（力積）
  //static btVector3 impulse3 = btVector3(0, 0, 0); // 撃力（力積）
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
    //assert(!"なにもないよ");
    return NullHandle;
  }

  // 初期位置と姿勢の設定
  btVector3 position = bullet::ToBTVector(_position);
  btQuaternion qrot(0.0f, 0.0f, 0.0f, 1.0f);  // 基本的にクォータニオンで設定する
  btDefaultMotionState* p_motion_state = new btDefaultMotionState(btTransform(qrot, position));

  // 質量と慣性モーメント（イナーシャ）の計算
  btVector3 inertia = btVector3(0.0f, 0.0f, 0.0f);
  btCollisionShape* p_collision_shape = p_shape_factory->Create();
  p_collision_shape->calculateLocalInertia(_mass, inertia);   // inertiaに計算結果が上書きされる

  // 剛体オブジェクト生成(質量，位置姿勢，形状，慣性モーメントを設定)
  // 剛体の生成には最低限、この4つの引数が必要になる
  btRigidBody* p_object_body = new btRigidBody(_mass, p_motion_state, p_collision_shape, inertia);

  // 反発係数の設定（デフォルトは0）
  p_object_body->setRestitution(_restitution);
  // 静止摩擦係数の設定（デフォルトは0.5）
  p_object_body->setFriction(_friction);
  // ワールドに追加
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
