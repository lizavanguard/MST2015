//==============================================================================
//
// ObjectInstancingModel
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "object_instancing_model.h"

#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
#include "Framework/Shader/shader_manager.h"
#include "Framework/Texture/texture_manager.h"
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Light/light.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
// TODO:
//------------------------------------------------
ObjectInstancingModel::ObjectInstancingModel(const char* p_filename, const unsigned int num_instances)
    : p_xmodel_data_(nullptr)
    , p_shader_(nullptr)
    , num_instancing_(num_instances) {
  instancing_matrices_.reserve(num_instancing_);
  for (unsigned int i = 0; i < num_instancing_; ++i) {
    D3DXMATRIX m;
    D3DXMatrixIdentity(&m);
    instancing_matrices_.push_back(m);
  }

  D3DVERTEXELEMENT9 elements[] = {
    {0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
    {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
    D3DDECL_END()
  };

  auto p_device = DeviceHolder::Instance().GetDevice();
  p_xmodel_data_ = ModelManager::Instance().Find(p_filename);

  p_xmodel_data_->p_mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, nullptr, nullptr, nullptr, nullptr);

  ID3DXMesh* pTempMesh = NULL;

  p_xmodel_data_->p_mesh->CloneMeshFVF(p_xmodel_data_->p_mesh->GetOptions(),
                                       p_xmodel_data_->p_mesh->GetFVF() | D3DFVF_NORMAL, p_device, &pTempMesh);

  D3DXComputeNormals(pTempMesh, NULL);
  p_xmodel_data_->p_mesh->Release();
  p_xmodel_data_->p_mesh = pTempMesh;

  liza::game::directx::AttachVertexDeclarationToMesh(DeviceHolder::Instance().GetDevice(), &p_xmodel_data_->p_mesh, elements);
  
  // インスタンシング
  D3DVERTEXELEMENT9 InstancingVertexElement[] = {
    {0/*パイプライン番号*/, 0/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_POSITION/*用途//D3DDECLUSAGE_POSITIONTは座標変換済み*/, 0/*用途番号*/},
    {0/*パイプライン番号*/, 12/*オフセット*/, D3DDECLTYPE_FLOAT3/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_NORMAL/*用途*/, 0/*用途番号*/},
    {0/*パイプライン番号*/, 24/*オフセット*/, D3DDECLTYPE_FLOAT2/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_TEXCOORD/*用途*/, 0/*用途番号*/},
    {1/*パイプライン番号*/, 0/*オフセット*/, D3DDECLTYPE_FLOAT1/*デクラレーションタイプ（型）*/, D3DDECLMETHOD_DEFAULT/*？*/, D3DDECLUSAGE_TEXCOORD/*用途*/, 1/*用途番号*/},
    D3DDECL_END()
  };

  p_declaration_ = nullptr;
  p_device->CreateVertexDeclaration(InstancingVertexElement, &p_declaration_);

  if (FAILED(p_device->CreateVertexBuffer(sizeof(float) * num_instancing_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &p_instancing_vertex_buffer_, nullptr))) {
    MessageBox(NULL, "FAILED", "CreateVertexBuffer", MB_OK);
    return;
  }

  float *p_index = nullptr;
  p_instancing_vertex_buffer_->Lock(0, 0, reinterpret_cast< void** >(&p_index), 0);

  for (unsigned int i(0); i < num_instancing_; ++i) {
    p_index[i] = (float)i;
  }

  p_instancing_vertex_buffer_->Unlock();

  ID3DXBuffer* p_error = nullptr;
  LPD3DXBUFFER compiled_code;

  if (FAILED(D3DXCompileShaderFromFile("hlsl/no_technique/instancing_xmodel_ps.hlsl", nullptr, nullptr,
    "PS", "ps_3_0", 0,
    &compiled_code, &p_error,
    &p_pixel_shader_constant))) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>(p_error->GetBufferPointer()),
      "D3DXCompileShaderFromFile", MB_OK);
    SafeRelease(p_error);
  }

  if (FAILED(p_device->CreatePixelShader(reinterpret_cast<DWORD*>(compiled_code->GetBufferPointer()),
    &p_pixel_shader))) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }

  SafeRelease(compiled_code);

  // ---------頂点シェーダー部分----------

  if (FAILED(D3DXCompileShaderFromFile("hlsl/no_technique/instancing_xmodel_vs.hlsl", nullptr, nullptr,
    "VS", "vs_3_0", 0,
    &compiled_code, &p_error,
    &p_vertex_shader_constant))) {
    MessageBox(nullptr, reinterpret_cast<LPCSTR>(p_error->GetBufferPointer()),
      "D3DXCompileShaderFromFile", MB_OK);
    SafeRelease(p_error);
  }

  if (FAILED(p_device->CreateVertexShader(reinterpret_cast<DWORD*>(compiled_code->GetBufferPointer()),
    &p_vertex_shader))) {
    MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
  }
  SafeRelease(compiled_code);

  p_xmodel_data_->p_mesh->GetVertexBuffer(&p_vertex_buffer_);
  p_xmodel_data_->p_mesh->GetIndexBuffer(&p_index_buffer_);

  num_vertices_ = (unsigned int)p_xmodel_data_->p_mesh->GetNumVertices();
  num_faces_ = (unsigned int)p_xmodel_data_->p_mesh->GetNumFaces();
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectInstancingModel::~ObjectInstancingModel() {
  SafeRelease(p_declaration_);
  SafeRelease(p_instancing_vertex_buffer_);
  SafeRelease(p_vertex_shader);
  SafeRelease(p_vertex_shader_constant);
  SafeRelease(p_pixel_shader);
  SafeRelease(p_pixel_shader_constant);
  SafeRelease(p_vertex_buffer_);
  SafeRelease(p_index_buffer_);
}

//------------------------------------------------
// Update instance-data
//------------------------------------------------
void ObjectInstancingModel::UpdateInstanceData(const unsigned int index, const D3DXVECTOR3& position, const D3DXVECTOR3& rotation) {
  D3DXMatrixIdentity(&instancing_matrices_[index]);
  D3DXMATRIX translation_matrix;
  D3DXMatrixTranslation(&translation_matrix, position.x, position.y, position.z);
  D3DXMATRIX rotation_matrix;
  D3DXMatrixRotationYawPitchRoll(&rotation_matrix, rotation.y, rotation.x, rotation.z);

  D3DXMATRIX world_matrix;
  world_matrix = rotation_matrix * translation_matrix;
  D3DXMatrixMultiply(&instancing_matrices_[index], &instancing_matrices_[index], &world_matrix);
}

//------------------------------------------------
// _Update
//------------------------------------------------
void ObjectInstancingModel::_Update(const float elapsed_time) {
  position_ += speed_ * elapsed_time;
  speed_ *= 0.99f;
}

//------------------------------------------------
// _Draw
//------------------------------------------------
void ObjectInstancingModel::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  auto& camera = CameraManager::Instance().GetMainCamera();
  D3DXMATRIX wvp = world_matrix_ * camera.GetViewMatrix() * camera.GetProjectionMatrix();

  p_device->SetVertexShader(p_vertex_shader);
  p_device->SetPixelShader(p_pixel_shader);

  D3DXMATRIX viewProj = camera.GetViewMatrix() * camera.GetProjectionMatrix();
  p_vertex_shader_constant->SetMatrix(p_device, "viewProj", &viewProj);

  const D3DXVECTOR3 light_direction = LightServiceLocator::Get()->GetDirection();
  p_vertex_shader_constant->SetFloatArray(p_device, "lightVec", (float*)&light_direction, 3);

  const int instancingMaxNum = 52;
  // 頂点宣言を設定
  p_device->SetVertexDeclaration(p_declaration_);
  // ストリームを設定
  // ストリームカウントからインスタンシング判定
  p_device->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | instancingMaxNum);
  p_device->SetStreamSourceFreq(static_cast<UINT>(1), D3DSTREAMSOURCE_INSTANCEDATA | static_cast<UINT>(1));
  p_device->SetStreamSource(0, p_vertex_buffer_, 0, sizeof(float) * (3 + 3 + 2));
  p_device->SetStreamSource(1, p_instancing_vertex_buffer_, 0, sizeof(float));
  // インデックスを設定
  p_device->SetIndices(p_index_buffer_);
  p_device->SetTexture(p_pixel_shader_constant->GetSamplerIndex("DiffuseSampler"), p_xmodel_data_->p_textures[0]);

  const unsigned int num_loops = (num_instancing_ / instancingMaxNum) + 1;
  int num_rest_instances_ = num_instancing_;
  for (unsigned int i = 0; i < num_loops; ++i) {
    const unsigned int start_index = instancingMaxNum * i;
    p_vertex_shader_constant->SetMatrixArray(p_device, "worldArray", &instancing_matrices_[start_index],
      (num_rest_instances_ <= instancingMaxNum) ? num_rest_instances_ : instancingMaxNum);
    num_rest_instances_ -= instancingMaxNum;
    p_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, num_vertices_, 0, num_faces_);
  }

  // インスタンシングの場合、元の設定に戻す
  p_device->SetStreamSourceFreq(0, 1);
  p_device->SetStreamSourceFreq(1, 1);

  p_device->SetPixelShader(nullptr);
  p_device->SetVertexShader(nullptr);
}
