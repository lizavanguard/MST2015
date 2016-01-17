//=============================================================================
//
// ゲームフェイズ処理ヘッダー [CGame.h]
// Author : 宗像 快
//
// TOOD:
//  管理クラスの作成
//  管理クラス要件としてはオブジェクトの追加
//  指定オブジェクトに対するインパクト等の追加
//  指定オブジェクトのワールド行列等の取得かな
//  あとは更新と停止？
//
//=============================================================================

// メモリーリーク設定あるとnewでエラー出るかな
// 導入方法
// インクルードパスにC:\Users\kai\Desktop\SP42Main\src
// デバッグとリリースにそれぞれのライブラリを設定
// Release用とDebug用のライブラリを両方とも同じディレクトリに置いた場合
#ifdef _DEBUG
#define BULLET_STR "_Debug.lib"
#define BULLET_PREFIX "lib/Debug/"
#else _REREASE
#define BULLET_STR ".lib"
#define BULLET_PREFIX "lib/Release/"
#endif

// 必要無いものはコメントアウト
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
// インクルード
//*****************************************************************************
#include "CGame.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
static const D3DXVECTOR3 InitCameraPosP = D3DXVECTOR3( 0.f, 10.0f, -15.0f );		// カメラ初期位置
static const D3DXVECTOR3 InitCameraPosR = D3DXVECTOR3( 0.f, 00.0f, 0.0f );			// カメラ初期位置
static const D3DXVECTOR3 InitLightPosP = D3DXVECTOR3( 0.f, -100.0f, 100.0f );		// ライト初期位置
static const D3DXVECTOR3 InitLightPosR = D3DXVECTOR3( 0.f, 0.0f, 0.0f );			// ライト初期位置

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
  //  CDebugProc::SetChar("Test Collision\n"); //衝突しているとTestCollisionが表示
  //  return btScalar(1);//本来は距離とかを求めて渡すっぽい
  //}
};

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame( void ) : 
m_pFade( NULL ),
m_pPause( NULL )
{
	
}

//=============================================================================
// ゲームフェイズ初期化処理
//=============================================================================
HRESULT CGame::Init( LPDIRECT3DDEVICE9 pDevice )
{
  bulletSimulateStep = 0;

  // 衝突検出方法の選択(デフォルトを選択)
  btDefaultCollisionConfiguration *config = new btDefaultCollisionConfiguration();
  btCollisionDispatcher *dispatcher = new btCollisionDispatcher(config);
  // ブロードフェーズ法の設定
  btDbvtBroadphase *broadphase = new btDbvtBroadphase();  // Dynamic AABB tree method
  // 拘束(剛体間リンク)のソルバ設定
  btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

  // Bulletのワールド作成
  btDynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
  // 重力の設定
  btDynamicsWorld->setGravity(btVector3(0, -9.8, 0));

  const btVector3 fallpos = btVector3(-0, -1, -0);

  // 落下オブジェクトの設定
  {
    // Collision（当たり判定）の形状を設定
    btCollisionShape *collision_shape = 0;
    //if( shape == CUBE )
    //  collision_shape = new btBoxShape(btVector3(0.5, 0.5, 0.5));
   // else if( shape == SPHERE )
      collision_shape = new btSphereShape(0.5);

    // 初期位置と姿勢の設定
      btVector3 pos = fallpos;
    btQuaternion qrot(0, 0, 0, 1);  // 基本的にクォータニオンで設定する
    btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

    // 質量と慣性モーメント（イナーシャ）の計算
    btScalar mass = btScalar(0.17);
    btVector3 inertia = btVector3(0, 0, 0);
    collision_shape->calculateLocalInertia(mass, inertia);   // inertiaに計算結果が上書きされる

    // 剛体オブジェクト生成(質量，位置姿勢，形状，慣性モーメントを設定)
    // 剛体の生成には最低限、この4つの引数が必要になる
    btFallBody = new btRigidBody(mass, motion_state, collision_shape, inertia);

    // 反発係数の設定（デフォルトは0）
    btScalar restitution = btScalar(0.8);
    btFallBody->setRestitution(restitution);
    // 静止摩擦係数の設定（デフォルトは0.5）
    //btScalar friction = btScalar(0.7);
    btScalar friction = btScalar(0.7);
    btFallBody->setFriction(friction);

    // 角速度
    //btFallBody->setAngularVelocity(btVector3(0, 0, 100));
    // 当たった時の回転力
    //btFallBody->setAngularFactor(btScalar(100));

    //btFallBody->setRollingFriction(btScalar(10));

    //btFallBody->applyTorqueImpulse(btVector3(100, 0, 0));
    //btFallBody->applyCentralForce(btVector3(100, 0, 0));

    // Bulletのワールドに追加
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
  // 柱の設定
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
  // 地面の設定
    {
    btCollisionShape *collision_shape = new btBoxShape(btVector3(groundSize[0] * 0.5, groundSize[1] * 0.5, groundSize[2] * 0.5));

      btVector3 pos = btVector3(0, -2, 0);
      btVector3 axis = btVector3(0, 0, 1);
      btScalar angle = 10.0 / RADIAN * 0.0f;   // 回転角はラジアン単位で指定（OpenGLのglRotateはdegree）
      btQuaternion qrot(axis, angle); // 回転軸と回転角からクォータニオンを計算（OpenGLのglRotateとは引数の順番が逆）
      btDefaultMotionState* motion_state = new btDefaultMotionState(btTransform(qrot, pos));

      // 質量を0にすると衝突しても動かない静的剛体になる（慣性モーメントも必ず0になるので必要無い）
      btGroundBody = new btRigidBody(0.0, motion_state, collision_shape);
      // 反発係数の設定（衝突する物体の反発係数と衝突される物体の反発係数を掛けた値が最終的な反発係数になる）
      btScalar restitution = btScalar(0.8);
      btGroundBody->setRestitution(restitution);

      // ワールドに剛体オブジェクトを追加
      btDynamicsWorld->addRigidBody(btGroundBody);
    }

	//// ゲーム終了フラグ初期化
	//CGame::SetEndFlg( FALSE );

	//// カメラ設定
	//CManager::GetCamera()->Init( InitCameraPosP, InitCameraPosR );

	//// ライト設定
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
	//// フェード
	//m_pFade = CFade::Create( pDevice );
	//m_pFade->Start( CFade::FADE_STATE_IN, D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), 60 );

	return S_OK;
}

//=============================================================================
// ゲームフェイズ終了処理
//=============================================================================
void CGame::Uninit( void )
{
  // オブジェクト破棄
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

  // ワールド破棄
  delete btDynamicsWorld->getBroadphase();
  delete btDynamicsWorld;

	//CScene::ReleaseAll();

	//CGame::SetEndFlg( FALSE );
}

//=============================================================================
// ゲームフェイズ更新処理
//=============================================================================
void CGame::Update( void )
{
  //////////////////////////////////////////////////////////////////
  // bullet
  //////////////////////////////////////////////////////////////////
  static double dt = 1.0f / 60.0f;
  btVector3 impulse = btVector3(0, 0, 150); // 撃力（力積）
  btVector3 impulse2 = btVector3(-0.0, 0, 0); // 撃力（力積）
  static btVector3 impulse3 = btVector3(0, 0, 0); // 撃力（力積）

 // // 5秒間隔で繰り返す
 // if( bulletSimulateStep == 300 ) {
 //   bulletSimulateStep = 0;
 //   impulse3 = btVector3(0, 0, 0); // 撃力（力積）
 //   CManager::SetPhase(CPhaseManager::PHASE_GAME);
 //   return;
 // }
 // // 最初だけ撃力を与える
 // if( bulletSimulateStep == 0 )
 //   btFallBody->applyCentralImpulse(impulse*dt);
 // // bulletのステップを進める
 // if( btDynamicsWorld ) {
 //   btDynamicsWorld->stepSimulation(dt);
 //   impulse3 += impulse2*dt;
 //   btFallBody->applyCentralImpulse(impulse3);
 // }
 // bulletSimulateStep++;

 // ContactSensorCallback callback;//callbackのクラスを作成
 // // 引数１と２の当たり判定
 // btDynamicsWorld->contactPairTest(btFallBody, btPallBody[9], callback);
 // // 引数１と全ての当たり判定
 // //btDynamicsWorld->contactTest(btFallBody, callback);
 // // 落下物
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

 // // 静止物
 // {
 //   for( int num = 0; num < kPallNum; num++ ) {
 //     // Bulletで計算したCollisionの位置を取得
 //     btVector3 pos = btPallBody[num]->getCenterOfMassPosition();
 //     // Bulletで計算した姿勢（回転角と回転軸）を取得
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

 // // 地面
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
	//// カメラ操作
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