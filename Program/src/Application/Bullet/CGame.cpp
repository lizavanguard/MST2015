//=============================================================================
//
// �Q�[���t�F�C�Y�����w�b�_�[ [CGame.h]
// Author : �@�� ��
//
// TOOD:
//  �Ǘ��N���X�̍쐬
//  �Ǘ��N���X�v���Ƃ��Ă̓I�u�W�F�N�g�̒ǉ�
//  �w��I�u�W�F�N�g�ɑ΂���C���p�N�g���̒ǉ�
//  �w��I�u�W�F�N�g�̃��[���h�s�񓙂̎擾����
//  ���Ƃ͍X�V�ƒ�~�H
//
//=============================================================================

// �������[���[�N�ݒ肠���new�ŃG���[�o�邩��
// �������@
// �C���N���[�h�p�X��C:\Users\kai\Desktop\SP42Main\src
// �f�o�b�O�ƃ����[�X�ɂ��ꂼ��̃��C�u������ݒ�
// Release�p��Debug�p�̃��C�u�����𗼕��Ƃ������f�B���N�g���ɒu�����ꍇ
#ifdef _DEBUG
#define BULLET_STR "_Debug.lib"
#define BULLET_PREFIX "lib/Debug/"
#else _REREASE
#define BULLET_STR ".lib"
#define BULLET_PREFIX "lib/Release/"
#endif

// �K�v�������̂̓R�����g�A�E�g
#pragma comment(lib, BULLET_PREFIX "BulletCollision" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletDynamics" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletFileLoader" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletMultiThreaded" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletSoftBody" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletSoftBodySolvers_OpenCL_Mini" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletWorldImporter" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "BulletXmlWorldImporter" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "ConvexDecomposition" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "GIMPACTUtils" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "GLUI" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "HACD" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "LinearMath" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "MiniCL" BULLET_STR)
#pragma comment(lib, BULLET_PREFIX "OpenGLSupport" BULLET_STR)

#undef BULLET_PREFIX
#undef BULLET_STR

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "CGame.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
static const D3DXVECTOR3 InitCameraPosP = D3DXVECTOR3( 0.f, 10.0f, -15.0f );		// �J���������ʒu
static const D3DXVECTOR3 InitCameraPosR = D3DXVECTOR3( 0.f, 00.0f, 0.0f );			// �J���������ʒu
static const D3DXVECTOR3 InitLightPosP = D3DXVECTOR3( 0.f, -100.0f, 100.0f );		// ���C�g�����ʒu
static const D3DXVECTOR3 InitLightPosR = D3DXVECTOR3( 0.f, 0.0f, 0.0f );			// ���C�g�����ʒu

static const double RADIAN = 180.0 / 3.1415;

struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {
  ContactSensorCallback() {};
  ~ContactSensorCallback() {};
  bool needsCollision(btBroadphaseProxy* proxy0) const {
    bool collides = ( proxy0->m_collisionFilterGroup & m_collisionFilterMask ) != 0;
    collides = collides && ( m_collisionFilterGroup & proxy0->m_collisionFilterMask );
    return collides;
  }
  //btScalar addSingleResult(btManifoldPoint &cp, const btCollisionObject colObj0, int partId0, int index0, const btCollisionObject *colObj1, int partId1, int index1)
  //btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
  //{
  //  CDebugProc::SetChar("Test Collision\n"); //�Փ˂��Ă����TestCollision���\��
  //  return btScalar(1);//�{���͋����Ƃ������߂ēn�����ۂ�
  //}
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame( void ) : 
m_pFade( NULL ),
m_pPause( NULL )
{
	
}

//=============================================================================
// �Q�[���t�F�C�Y����������
//=============================================================================
HRESULT CGame::Init( LPDIRECT3DDEVICE9 pDevice )
{
  bulletSimulateStep = 0;

  // �Փˌ��o���@�̑I��(�f�t�H���g��I��)
  btDefaultCollisionConfiguration *config = new btDefaultCollisionConfiguration();
  btCollisionDispatcher *dispatcher = new btCollisionDispatcher(config);
  // �u���[�h�t�F�[�Y�@�̐ݒ�
  btDbvtBroadphase *broadphase = new btDbvtBroadphase();  // Dynamic AABB tree method
  // �S��(���̊ԃ����N)�̃\���o�ݒ�
  btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

  // Bullet�̃��[���h�쐬
  btDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
  // �d�͂̐ݒ�
  btDynamicsWorld->setGravity(btVector3(0, -9.8, 0));

  const btVector3 fallpos = btVector3(-0, -1, -0);

  // �����I�u�W�F�N�g�̐ݒ�
  {
    // Collision�i�����蔻��j�̌`���ݒ�
    btCollisionShape *collision_shape = 0;
    //if( shape == CUBE )
    //  collision_shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
   // else if( shape == SPHERE )
      collision_shape = new btSphereShape(0.5);

    // �����ʒu�Ǝp���̐ݒ�
      btVector3 pos = fallpos;
    btQuaternion qrot(0, 0, 0, 1);  // ��{�I�ɃN�H�[�^�j�I���Őݒ肷��
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

    // ���ʂƊ������[�����g�i�C�i�[�V���j�̌v�Z
    btScalar mass = btScalar(0.17);
    btVector3 inertia = btVector3(0, 0, 0);
    collision_shape->calculateLocalInertia(mass, inertia);   // inertia�Ɍv�Z���ʂ��㏑�������

    // ���̃I�u�W�F�N�g����(���ʁC�ʒu�p���C�`��C�������[�����g��ݒ�)
    // ���̂̐����ɂ͍Œ���A����4�̈������K�v�ɂȂ�
    btFallBody = new btRigidBody(mass, motion_state, collision_shape, inertia);

    // �����W���̐ݒ�i�f�t�H���g��0�j
    btScalar restitution = btScalar(0.8);
    btFallBody->setRestitution(restitution);
    // �Î~���C�W���̐ݒ�i�f�t�H���g��0.5�j
    //btScalar friction = btScalar(0.7);
    btScalar friction = btScalar(0.7);
    btFallBody->setFriction(friction);

    // �p���x
    //btFallBody->setAngularVelocity(btVector3(0, 0, 100));
    // �����������̉�]��
    //btFallBody->setAngularFactor(btScalar(100));

    //btFallBody->setRollingFriction(btScalar(10));

    //btFallBody->applyTorqueImpulse(btVector3(100, 0, 0));
    //btFallBody->applyCentralForce(btVector3(100, 0, 0));

    // Bullet�̃��[���h�ɒǉ�
    btDynamicsWorld->addRigidBody(btFallBody);
  }

  const btVector3 pallSize(0.4, 2.0, 0.4);
  btVector3 pallpos[kPallNum] = { btVector3(0, -1.0, 5),
                           btVector3(-0.5, -1.0, 6.5),
                           btVector3(0.5, -1.0, 6.5),
                           btVector3(0, -1.0, 8),
                           btVector3(1, -1.0, 8),
                           btVector3(-1, -1.0, 8),
                           btVector3(1.5, -1.0, 9.5),
                           btVector3(0.5, -1.0, 9.5),
                           btVector3(-0.5, -1.0, 9.5),
                           btVector3(-1.5, -1.0, 9.5),
  };
  // ���̐ݒ�
    {
    for( int num = 0; num<kPallNum; num++ ) {
        btCollisionShape *collision_shape = new btBoxShape(btVector3(pallSize[0] * 0.5, pallSize[1] * 0.5, pallSize[2] * 0.5));
        btVector3 pos = pallpos[num];
        btQuaternion qrot(0, 0, 0, 1);
        btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

        btScalar mass = btScalar(0.005);
        btVector3 inertia = btVector3(0, 0, 0);
        collision_shape->calculateLocalInertia(mass, inertia);

        btPallBody[num] = new btRigidBody(mass, motion_state, collision_shape, inertia);

        //btScalar restitution = btScalar(0.1);
        btScalar restitution = btScalar(0.5);
        btPallBody[num]->setRestitution(restitution);

        btScalar friction = btScalar(1);
        btPallBody[num]->setFriction(friction);

        btDynamicsWorld->addRigidBody(btPallBody[num]);
      }
    }
    
  const btVector3 groundSize(20, 0.1, 50);
  // �n�ʂ̐ݒ�
    {
    btCollisionShape *collision_shape = new btBoxShape(btVector3(groundSize[0] * 0.5, groundSize[1] * 0.5, groundSize[2] * 0.5));

      btVector3 pos = btVector3(0, -2, 0);
      btVector3 axis = btVector3(0, 0, 1);
      btScalar angle = 10.0 / RADIAN * 0.0f;   // ��]�p�̓��W�A���P�ʂŎw��iOpenGL��glRotate��degree�j
      btQuaternion qrot(axis, angle); // ��]���Ɖ�]�p����N�H�[�^�j�I�����v�Z�iOpenGL��glRotate�Ƃ͈����̏��Ԃ��t�j
      btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

      // ���ʂ�0�ɂ���ƏՓ˂��Ă������Ȃ��ÓI���̂ɂȂ�i�������[�����g���K��0�ɂȂ�̂ŕK�v�����j
      btGroundBody = new btRigidBody(0.0, motion_state, collision_shape);
      // �����W���̐ݒ�i�Փ˂��镨�̂̔����W���ƏՓ˂���镨�̂̔����W�����|�����l���ŏI�I�Ȕ����W���ɂȂ�j
      btScalar restitution = btScalar(0.8);
      btGroundBody->setRestitution(restitution);

      // ���[���h�ɍ��̃I�u�W�F�N�g��ǉ�
      btDynamicsWorld->addRigidBody(btGroundBody);
    }

	//// �Q�[���I���t���O������
	//CGame::SetEndFlg( FALSE );

	//// �J�����ݒ�
	//CManager::GetCamera()->Init( InitCameraPosP, InitCameraPosR );

	//// ���C�g�ݒ�
	//CManager::GetLight()->Init( InitLightPosP, InitLightPosR );
	//
 // p_ground = CSceneCube::Create(pDevice, (float)groundSize[0], (float)groundSize[1], (float)groundSize[2]);
 // p_ground->SetPos(0.0f, -2.0f, 0.0f);
 // p_fall_box = CSceneCube::Create(pDevice, 1.0f, 1.0f, 1.0f);
 // p_fall_box->SetPos((float)fallpos[0], (float)fallpos[1], (float)fallpos[2]);

 // for( int num = 0; num < kPallNum; num++ ) {
 //   p_pall_box[num] = CSceneCube::Create(pDevice, (float)pallSize[0], (float)pallSize[1], (float)pallSize[2]);
 //   p_pall_box[num]->SetPos((float)pallpos[num][0], (float)pallpos[num][1], (float)pallpos[num][2]);
 // }
 // 
	//// �t�F�[�h
	//m_pFade = CFade::Create( pDevice );
	//m_pFade->Start( CFade::FADE_STATE_IN, D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), 60 );

	return S_OK;
}

//=============================================================================
// �Q�[���t�F�C�Y�I������
//=============================================================================
void CGame::Uninit( void )
{
  // �I�u�W�F�N�g�j��
  delete btFallBody->getMotionState();
  btDynamicsWorld->removeRigidBody(btFallBody);
  delete btFallBody;

  for( int num = 0; num<kPallNum; num++ ) {
    delete btPallBody[num]->getMotionState();
    btDynamicsWorld->removeRigidBody(btPallBody[num]);
    delete btPallBody[num];
  }

  delete btGroundBody->getMotionState();
  btDynamicsWorld->removeRigidBody(btGroundBody);
  delete btGroundBody;

  // ���[���h�j��
  delete btDynamicsWorld->getBroadphase();
  delete btDynamicsWorld;

	//CScene::ReleaseAll();

	//CGame::SetEndFlg( FALSE );
}

//=============================================================================
// �Q�[���t�F�C�Y�X�V����
//=============================================================================
void CGame::Update( void )
{
  //////////////////////////////////////////////////////////////////
  // bullet
  //////////////////////////////////////////////////////////////////
  static double dt = 1.0f / 60.0f;
  btVector3 impulse = btVector3(0, 0, 150); // ���́i�͐ρj
  btVector3 impulse2 = btVector3(-0.0, 0, 0); // ���́i�͐ρj
  static btVector3 impulse3 = btVector3(0, 0, 0); // ���́i�͐ρj

 // // 5�b�Ԋu�ŌJ��Ԃ�
 // if( bulletSimulateStep == 300 ) {
 //   bulletSimulateStep = 0;
 //   impulse3 = btVector3(0, 0, 0); // ���́i�͐ρj
 //   CManager::SetPhase(CPhaseManager::PHASE_GAME);
 //   return;
 // }
 // // �ŏ��������͂�^����
 // if( bulletSimulateStep == 0 )
 //   btFallBody->applyCentralImpulse(impulse*dt);
 // // bullet�̃X�e�b�v��i�߂�
 // if( btDynamicsWorld ) {
 //   btDynamicsWorld->stepSimulation(dt);
 //   impulse3 += impulse2*dt;
 //   btFallBody->applyCentralImpulse(impulse3);
 // }
 // bulletSimulateStep++;

 // ContactSensorCallback callback;//callback�̃N���X���쐬
 // // �����P�ƂQ�̓����蔻��
 // btDynamicsWorld->contactPairTest(btFallBody, btPallBody[9], callback);
 // // �����P�ƑS�Ă̓����蔻��
 // //btDynamicsWorld->contactTest(btFallBody, callback);
 // // ������
 // {
 //   btVector3 pos = btFallBody->getCenterOfMassPosition();
 //   btScalar rot = btScalar(btFallBody->getOrientation().getAngle());
 //   btVector3 axis = btFallBody->getOrientation().getAxis();
 //   D3DXQUATERNION quatRot;
 //   D3DXVECTOR3 vec3axis((float)axis[0], (float)axis[1], (float)axis[2]);
 //   D3DXQuaternionRotationAxis(&quatRot, &vec3axis, (float)rot);
 //   D3DXMATRIX mtxRot;
 //   D3DXMatrixRotationQuaternion(&mtxRot, &quatRot);
 //   p_fall_box->SetPos((float)pos[0], (float)pos[1], (float)pos[2]);
 //   p_fall_box->SetRotMatrix(mtxRot);
 // }

 // // �Î~��
 // {
 //   for( int num = 0; num < kPallNum; num++ ) {
 //     // Bullet�Ōv�Z����Collision�̈ʒu���擾
 //     btVector3 pos = btPallBody[num]->getCenterOfMassPosition();
 //     // Bullet�Ōv�Z�����p���i��]�p�Ɖ�]���j���擾
 //     btScalar rot = btScalar(btPallBody[num]->getOrientation().getAngle());
 //     btVector3 axis = btPallBody[num]->getOrientation().getAxis();
 //     D3DXQUATERNION quatRot;
 //     D3DXVECTOR3 vec3axis((float)axis[0], (float)axis[1], (float)axis[2]);
 //     D3DXQuaternionRotationAxis(&quatRot, &vec3axis, (float)rot);
 //     D3DXMATRIX mtxRot;
 //     D3DXMatrixRotationQuaternion(&mtxRot, &quatRot);
 //     p_pall_box[num]->SetPos((float)pos[0], (float)pos[1], (float)pos[2]);
 //     p_pall_box[num]->SetRotMatrix(mtxRot);
 //   }
 // }

 // // �n��
 // {
 //   btVector3 pos = btGroundBody->getCenterOfMassPosition();
 //   btScalar rot = btScalar(btGroundBody->getOrientation().getAngle());
 //   btVector3 axis = btGroundBody->getOrientation().getAxis();
 //   D3DXQUATERNION quatRot;
 //   D3DXVECTOR3 vec3axis((float)axis[0], (float)axis[1], (float)axis[2]);
 //   D3DXQuaternionRotationAxis(&quatRot, &vec3axis, (float)rot);
 //   D3DXMATRIX mtxRot;
 //   D3DXMatrixRotationQuaternion(&mtxRot, &quatRot);
 //   p_ground->SetPos((float)pos[0], (float)pos[1], (float)pos[2]);
 //   p_ground->SetRotMatrix(mtxRot);
 // }

	//auto pKeyboard = CManager::GetKeyboard();
	//auto pJoypad = CManager::GetJoypad();
 // const float CAMERA_ADD_ROT = D3DX_PI * 0.01f;
	//// �J��������
	//auto pCamera = CManager::GetCamera();
	//if( pKeyboard->GetPressKey( DIK_U ) || pJoypad->GetPressKey( CInputJoypad::JOYSTICK_RIGHT_RIGHT ) )
	//{
	//	pCamera->AddRot( D3DXVECTOR3( 0.0f, CAMERA_ADD_ROT, 0.0f ) );
	//}
	//else if( pKeyboard->GetPressKey( DIK_O ) || pJoypad->GetPressKey( CInputJoypad::JOYSTICK_LEFT_RIGHT ) )
	//{
	//	pCamera->AddRot( D3DXVECTOR3( 0.0f, -CAMERA_ADD_ROT, 0.0f ) );
	//}
}
// EOF