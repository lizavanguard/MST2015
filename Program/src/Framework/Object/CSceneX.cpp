//=============================================================================
//
// シーンＸモデル処理 [CSceneX.cpp]
// Author : 宗像 快
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "CSceneX.h"
#include "CManager.h"
#include "Math.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const char *FILE_TEXTURE_PATH = "data/TEXTURE/";
const int MAX_FILE_NAME = 64;
const int instancingNum = 104;

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneX::CSceneX(LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, OBJTYPE objType, int nPriority) :
CScene(pD3DDevice, objType, nPriority),
m_ppTex(NULL),
m_pD3DXMesh(NULL),
m_pD3DXBuffMat(NULL),
m_nNumMat(0),
m_vec3Scl(1.f, 1.f, 1.f),
m_pDeclaration(NULL),
m_bExistTex(FALSE),
m_pVS(NULL),
m_pVSC(NULL),
m_pPS(NULL),
m_pPSC(NULL),
lightMode(0.0f),
drawFlg(false)
{
	D3DXMatrixIdentity( &m_mtxWorld );

	LPD3DXBUFFER adjBuffer = NULL;

	// 頂点バッファの生成
	if( FAILED( D3DXLoadMeshFromX( pFileName,
									D3DXMESH_SYSTEMMEM,
									pD3DDevice,
									&adjBuffer,
									&m_pD3DXBuffMat,
									NULL,
									&m_nNumMat,
									&m_pD3DXMesh ) ) )
	{
		MessageBox( NULL, "モデルの読み込みに失敗しました", "エラー", MB_OK | MB_ICONERROR );
		return;
	}

	//Xファイルに法線がない場合は、法線を書き込む
	//if( !( m_pD3DXMesh->GetFVF() & D3DFVF_NORMAL ) )
	//{
		ID3DXMesh* pTempMesh = NULL;
		
		m_pD3DXMesh->CloneMeshFVF( m_pD3DXMesh->GetOptions(),
				m_pD3DXMesh->GetFVF() | D3DFVF_NORMAL, pD3DDevice, &pTempMesh );
	
		D3DXComputeNormals(pTempMesh, NULL);
		m_pD3DXMesh->Release();
		m_pD3DXMesh = pTempMesh;
	//}
	
	// テクスチャポインタ作成
	m_ppTex = new LPDIRECT3DTEXTURE9[m_nNumMat];

	D3DXMATERIAL *pD3DXMat;

	pD3DXMat = reinterpret_cast<D3DXMATERIAL *>( m_pD3DXBuffMat->GetBufferPointer() );

	char aFileName[ MAX_FILE_NAME ] = "";	// テクスチャパス作成用

	for( unsigned int cnt = 0; cnt < m_nNumMat; ++cnt )
	{
		// テクスチャ情報があれば、設定
		if( pD3DXMat[cnt].pTextureFilename != NULL )
		{
			ZeroMemory( &aFileName[ 0 ], sizeof( aFileName ) );
			// テクスチャパス作成
			strcpy_s( &aFileName[ 0 ], sizeof( char ) * MAX_FILE_NAME, FILE_TEXTURE_PATH );
			strcat_s( &aFileName[ 0 ], sizeof( char ) * MAX_FILE_NAME, pD3DXMat[cnt].pTextureFilename );
			// テクスチャ設定
			m_ppTex[cnt] = CTexture::GetTexture( &aFileName[ 0 ] );

			m_bExistTex = TRUE;
		}
		else
		{
			m_ppTex[cnt] = NULL;
		}
	}



	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 0/*パイプライン番号*/, 0/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_POSITION/*用途//D3DDECLUSAGE_POSITIONTは座標変換済み*/, 0/*用途番号*/ },
		{ 0/*パイプライン番号*/, 12/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_NORMAL/*用途*/, 0/*用途番号*/ },
    { 0/*パイプライン番号*/, 24/*オフセット*/, D3DDECLTYPE_FLOAT2/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_TEXCOORD/*用途*/, 0/*用途番号*/ },
		D3DDECL_END()
	};

	m_pD3DDevice->CreateVertexDeclaration( vertexElement, &m_pDeclaration );

  if(FAILED(m_pD3DXMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (LPDWORD)adjBuffer->GetBufferPointer(), NULL/*最適化された隣接情報*/, NULL/*面のインデックス*/, NULL/*頂点のインデックス*/)))
  {
    MessageBox(NULL, "モデルのオプティマイザに失敗しました", "エラー", MB_OK | MB_ICONERROR);
    return;
  }

  SAFE_RELEASE(adjBuffer);

  // コンバート
  LPD3DXMESH pOldMesh = m_pD3DXMesh;

  if(FAILED(pOldMesh->CloneMesh(D3DXMESH_MANAGED, vertexElement, m_pD3DDevice, &m_pD3DXMesh)))
  {
    MessageBox(NULL, "モデルのエレメント設定に失敗しました", "エラー", MB_OK | MB_ICONERROR);
    return;
  }

  SAFE_RELEASE(pOldMesh);

  // ---------ピクセルシェーダー部分----------
  HRESULT hr;
  LPD3DXBUFFER err;
  LPD3DXBUFFER code;

  hr = D3DXCompileShaderFromFile("data/SHADER/basicPS.hlsl"	// シェーダーファイル名
    , NULL
    , NULL
    , "PS"				// シェーダープログラムのエントリポイントの関数名
    , "ps_2_0"			// シェーダーバージョン
    , 0
    , &code				// コンパイル後のシェーダーバイナリ
    , &err
    , &m_pPSC);
  if (FAILED(hr)) {
    MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
    err->Release();
    return;
  }

  hr = m_pD3DDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_pPS);
  if(FAILED(hr))
  {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
    return;
  }

  SAFE_RELEASE(code);

  //----------------------------------------------------------------------------

  // ---------頂点シェーダー部分----------
  hr = D3DXCompileShaderFromFile("data/SHADER/basicVS.hlsl"	// シェーダーファイル名
    , NULL
    , NULL
    , "VS"				// シェーダープログラムのエントリポイントの関数名
    , "vs_2_0"			// シェーダーバージョン
    , 0
    , &code				// コンパイル後のシェーダーバイナリ
    , &err
    , &m_pVSC);
  if(FAILED(hr))
  {
    MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
    err->Release();
    return;
  }

  hr = m_pD3DDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_pVS);
  if(FAILED(hr))
  {
    MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
    return;
  }

  SAFE_RELEASE(code);
  //---------------------------------------------------------------------

  // インスタンシング
  D3DVERTEXELEMENT9 InstancingVertexElement[] = {
      { 0/*パイプライン番号*/, 0/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_POSITION/*用途//D3DDECLUSAGE_POSITIONTは座標変換済み*/, 0/*用途番号*/ },
      { 0/*パイプライン番号*/, 12/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_NORMAL/*用途*/, 0/*用途番号*/ },
      { 0/*パイプライン番号*/, 24/*オフセット*/, D3DDECLTYPE_FLOAT2/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_TEXCOORD/*用途*/, 0/*用途番号*/ },
      { 1/*パイプライン番号*/, 0/*オフセット*/, D3DDECLTYPE_FLOAT1/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_TEXCOORD/*用途*/, 1/*用途番号*/ },
      D3DDECL_END()
  };

  m_pD3DDevice->CreateVertexDeclaration(InstancingVertexElement, &p_declaration_);
 
  if( FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(float) * instancingNum, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &p_instancing_vertex_buffer_, nullptr)) ) {
    MessageBox(NULL, "FAILED", "CreateVertexBuffer", MB_OK);
    return;
  }

  float *p_index = nullptr;
  p_instancing_vertex_buffer_->Lock(0, 0, reinterpret_cast< void** >( &p_index ), 0);

  for( int i(0); i < instancingNum; ++i ) {
    p_index[i] = i;
  }

  p_instancing_vertex_buffer_->Unlock();

  ID3DXBuffer* p_error = nullptr;
  LPD3DXBUFFER compiled_code;

  if( FAILED(D3DXCompileShaderFromFile("data/SHADER/instancing_xmodel_ps.hlsl", nullptr, nullptr,
    "PS", "ps_3_0", 0,
    &compiled_code, &p_error,
    &p_pixel_shader_constant)) ) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>( p_error->GetBufferPointer() ),
               "D3DXCompileShaderFromFile", MB_OK);
    SAFE_RELEASE(p_error);
  }

  if( FAILED(m_pD3DDevice->CreatePixelShader(reinterpret_cast<DWORD*>( compiled_code->GetBufferPointer() ),
    &p_pixel_shader)) ) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }

  SAFE_RELEASE(compiled_code);

  // ---------頂点シェーダー部分----------

  if( FAILED(D3DXCompileShaderFromFile("data/SHADER/instancing_xmodel_vs.hlsl", nullptr, nullptr,
    "VS", "vs_3_0", 0,
    &compiled_code, &p_error,
    &p_vertex_shader_constant)) ) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>( p_error->GetBufferPointer() ),
               "D3DXCompileShaderFromFile", MB_OK);
    SAFE_RELEASE(p_error);
  }

  if( FAILED(m_pD3DDevice->CreateVertexShader(reinterpret_cast<DWORD*>( compiled_code->GetBufferPointer() ),
    &p_vertex_shader)) ) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }
  SAFE_RELEASE(compiled_code);

  m_pD3DXMesh->GetVertexBuffer(&p_vertex_buffer_);
  m_pD3DXMesh->GetIndexBuffer(&p_index_buffer_);

  num_vertices_ = (unsigned int)m_pD3DXMesh->GetNumVertices();
  num_faces_ = (unsigned int)m_pD3DXMesh->GetNumFaces();

  SAFE_RELEASE(m_pD3DXMesh);
  SAFE_RELEASE(m_pD3DXBuffMat);
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
	//SAFE_RELEASE( m_pD3DXMesh );
	//SAFE_RELEASE( m_pD3DXBuffMat );
  SAFE_DELETE_ARRAY(m_ppTex);
  SAFE_RELEASE(m_pDeclaration);

  SAFE_RELEASE(p_declaration_);
  SAFE_RELEASE(p_instancing_vertex_buffer_);
  SAFE_RELEASE(p_vertex_shader);
  SAFE_RELEASE(p_vertex_shader_constant);
  SAFE_RELEASE(p_pixel_shader);
  SAFE_RELEASE(p_pixel_shader_constant);
  SAFE_RELEASE(p_vertex_buffer_);
  SAFE_RELEASE(p_index_buffer_);

  SAFE_RELEASE(m_pVS);
  SAFE_RELEASE(m_pVSC);
  SAFE_RELEASE(m_pPS);
  SAFE_RELEASE(m_pPSC);
}

//=============================================================================
// CSceneX初期化処理
//=============================================================================
HRESULT CSceneX::Init( void )
{
	return S_OK;
}

//=============================================================================
// CSceneX終了処理
//=============================================================================
void CSceneX::Uninit( void )
{
	this->Release();
}

//=============================================================================
// CSceneX更新処理
//=============================================================================
void CSceneX::Update( void )
{
  
}

//=============================================================================
// CSceneX描画処理
//=============================================================================
void CSceneX::Draw( void )
{
  if(!drawFlg)
  {
    return;
  }
#if 0
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
  //m_vec3Rot.z+= D3DX_PI * 0.01f;
	D3DXMatrixIdentity( &m_mtxWorld );
	D3DXMatrixScaling( &mtxScl, m_vec3Scl.x, m_vec3Scl.y, m_vec3Scl.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxScl );

	D3DXMatrixRotationYawPitchRoll( &mtxRot, m_vec3Rot.y, m_vec3Rot.x, m_vec3Rot.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );

	D3DXMatrixTranslation( &mtxTranslate, m_vec3Pos.x, m_vec3Pos.y, m_vec3Pos.z );
	D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxTranslate );

	//m_pD3DDevice->SetVertexDeclaration( m_pDeclaration );

  const auto pCamera = CManager::GetCamera();
  D3DXMATRIX View = pCamera->GetMtxView();
  D3DXMATRIX Projection = pCamera->GetMtxProj();
  D3DXMATRIX WVP = m_mtxWorld * View * Projection;
  D3DXVECTOR3 cameraVec = pCamera->GetVec();

  const auto pLight = CManager::GetLight();
  // ライトベクトルのローカル化
  D3DXVECTOR3 localLightVec(0.0f, -1.0f, 1.0f);// = pLight->GetLightDir();
  
  D3DXMATRIX invWorld;
  D3DXVECTOR4 light(localLightVec, 0.0f);
  D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
  D3DXVec4Transform(&light, &light, &invWorld);
  D3DXVec4Normalize(&light, &light);
  localLightVec.x = light.x;
  localLightVec.y = light.y;
  localLightVec.z = light.z;

  D3DXVECTOR4 camera(cameraVec, 0.0f);
  D3DXVec4Transform(&camera, &camera, &invWorld);
  D3DXVec4Normalize(&camera, &camera);
  cameraVec.x = camera.x;
  cameraVec.y = camera.y;
  cameraVec.z = camera.z;

	D3DXMATERIAL *pD3DXMat = reinterpret_cast<D3DXMATERIAL *>( m_pD3DXBuffMat->GetBufferPointer() );
  // シェーダーの適用
  m_pD3DDevice->SetVertexShader(m_pVS);
  m_pD3DDevice->SetPixelShader(m_pPS);

  m_pD3DDevice->SetSamplerState(m_pPSC->GetSamplerIndex("DiffuseSampler"), D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  m_pD3DDevice->SetSamplerState(m_pPSC->GetSamplerIndex("DiffuseSampler"), D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
  m_pD3DDevice->SetSamplerState(m_pPSC->GetSamplerIndex("DiffuseSampler"), D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
  m_pD3DDevice->SetSamplerState(m_pPSC->GetSamplerIndex("DiffuseSampler"), D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

  m_pVSC->SetFloat(m_pD3DDevice, "gValue", lightMode);
  m_pVSC->SetMatrix(m_pD3DDevice, "gWVP", &WVP);
  m_pVSC->SetFloatArray(m_pD3DDevice, "gLightDir", (float*)&localLightVec, 3);
  m_pVSC->SetFloatArray(m_pD3DDevice, "gCameraDir", (float*)&cameraVec, 3);

  D3DXVECTOR4 ambient(0.1f, 0.1f, 0.0f, 0.0f);
  m_pVSC->SetFloatArray(m_pD3DDevice, "gAmbient", (float*)&ambient, 4);

  // マテリアル情報を取得
  D3DMATERIAL9 DefaultMaterial;
  m_pD3DDevice->GetMaterial(&DefaultMaterial);

	for( unsigned int nCntMat = 0; nCntMat < m_nNumMat; ++nCntMat )
	{
    m_pD3DDevice->SetTexture(m_pPSC->GetSamplerIndex("DiffuseSampler"), m_ppTex[nCntMat]);
    m_pVSC->SetFloatArray(m_pD3DDevice, "gColor", (float*)&pD3DXMat[nCntMat].MatD3D.Diffuse, 4);
		m_pD3DXMesh->DrawSubset( nCntMat );
	}
	
  m_pD3DDevice->SetVertexShader(NULL);
  m_pD3DDevice->SetPixelShader(NULL);

  // マテリアルをセット
  m_pD3DDevice->SetMaterial(&DefaultMaterial);
#else
  m_pD3DDevice->SetVertexShader(p_vertex_shader);
  m_pD3DDevice->SetPixelShader(p_pixel_shader);

  const auto p_camera = CManager::GetCamera();
  D3DXMATRIX viewProj = p_camera->GetMtxView() * p_camera->GetMtxProj();
  p_vertex_shader_constant->SetMatrix(m_pD3DDevice, "viewProj", &viewProj);

  D3DXVECTOR3 lightVec(0.0f, -1.0f, -1.0f);
  D3DXVec3Normalize(&lightVec, &lightVec);
  p_vertex_shader_constant->SetFloatArray(m_pD3DDevice, "lightVec", (float*)&lightVec, 3);

  const int instancingMaxNum = 52;
  D3DXMATRIX instancingWorld[instancingNum];
  
  for( int i(0); i < instancingNum; ++i ) {
    D3DXMatrixIdentity(&instancingWorld[i]);
    D3DXMATRIX trans;
    float g = 0.0f;
    if( ( i - instancingMaxNum ) > 0 ) {
      g = 1.0f;
    }
    D3DXVECTOR3 position_(-600.0f, 0.0f, 0.0f + 120.0f * g);
    D3DXMatrixTranslation(&trans, position_.x + 10.0f * i, position_.y, position_.z);
    D3DXMatrixMultiply(&instancingWorld[i], &instancingWorld[i], &trans);
  }
  p_vertex_shader_constant->SetMatrixArray(m_pD3DDevice, "worldArray", instancingWorld, instancingMaxNum);

  // 頂点宣言を設定
  m_pD3DDevice->SetVertexDeclaration(p_declaration_);
  // ストリームを設定
  // ストリームカウントからインスタンシング判定
  m_pD3DDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | instancingMaxNum);
  m_pD3DDevice->SetStreamSourceFreq(static_cast<UINT>( 1 ), D3DSTREAMSOURCE_INSTANCEDATA | static_cast<UINT>( 1 ));
  m_pD3DDevice->SetStreamSource(0, p_vertex_buffer_, 0, sizeof(float) * ( 3 + 3 + 2 ));
  m_pD3DDevice->SetStreamSource(1, p_instancing_vertex_buffer_, 0, sizeof(float));
  // インデックスを設定
  m_pD3DDevice->SetIndices(p_index_buffer_);
  m_pD3DDevice->SetTexture(p_pixel_shader_constant->GetSamplerIndex("DiffuseSampler"), CTexture::GetTexture(CTexture::TEXTURE_PIN));

  m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, num_vertices_, 0, num_faces_);

  p_vertex_shader_constant->SetMatrixArray(m_pD3DDevice, "worldArray", &instancingWorld[instancingMaxNum], instancingNum - instancingMaxNum);
  m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, num_vertices_, 0, num_faces_);
  // インスタンシングの場合、元の設定に戻す
  m_pD3DDevice->SetStreamSourceFreq(0, 1);
  m_pD3DDevice->SetStreamSourceFreq(1, 1);
#endif
}

//=============================================================================
// CSceneX座標設定処理
//=============================================================================
void CSceneX::SetPos( float x, float y, float z )
{
	m_vec3Pos.x = x;
	m_vec3Pos.y = y;
	m_vec3Pos.z = z;
}

//=============================================================================
// CSceneX座標設定処理
//=============================================================================
void CSceneX::SetPos( D3DXVECTOR3 pos )
{
	m_vec3Pos = pos;
}

//=============================================================================
// CSceneX座標取得処理
//=============================================================================
D3DXVECTOR3 CSceneX::GetPos( void )
{
	return m_vec3Pos;
}

//=============================================================================
// CSceneX回転設定処理
//=============================================================================
void CSceneX::SetRot( float x, float y, float z )
{
	m_vec3Rot.x = x;
	m_vec3Rot.y = y;
	m_vec3Rot.z = z;
}

//=============================================================================
// CSceneX回転設定処理
//=============================================================================
void CSceneX::SetRot( D3DXVECTOR3 rot )
{
	m_vec3Rot = rot;
}

//=============================================================================
// CSceneX回転取得処理
//=============================================================================
D3DXVECTOR3 CSceneX::GetRot( void )
{
	return m_vec3Rot;
}

//=============================================================================
// CSceneXテクスチャ設定処理
//=============================================================================
void CSceneX::SetTexture( CTexture::TEXTURE_TYPE type )
{
	
}

//=============================================================================
// CSceneXテクスチャ設定処理
//=============================================================================
CSceneX *CSceneX::Create( LPDIRECT3DDEVICE9 pD3DDevice, const char *pFileName, int nPriority )
{
	CSceneX *p = new CSceneX( pD3DDevice, pFileName, CScene::OBJTYPE_X, nPriority );
	p->Init();
	p->LinkList();
	return p;
}
// EOF