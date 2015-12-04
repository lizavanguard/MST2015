//==============================================================================
//
// Test2
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Test2.h"

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Camera/camera.h"
#include "Framework/Camera/camera_manager.h"
// �`��Ǘ��C���X�^���X�̐���
::EffekseerRenderer::Renderer* renderer;
// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
::Effekseer::Manager* manager;

// �G�t�F�N�g�̓Ǎ�
Effekseer::Effect* effect;
// �G�t�F�N�g�̍Đ�
Effekseer::Handle handle;

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Test2::Test2() {
  // �`��Ǘ��C���X�^���X�̐���
  renderer = ::EffekseerRendererDX9::Renderer::Create(DeviceHolder::Instance().GetDevice(), 2000);
  // �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
  manager = ::Effekseer::Manager::Create(2000);

  // �`����@�̎w��A�Ǝ��Ɋg�����Ȃ������`���ł��B
  manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
  manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
  manager->SetRingRenderer(renderer->CreateRingRenderer());
  // �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
  manager->SetTextureLoader(renderer->CreateTextureLoader());
  // ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
  //manager->SetCoordinateSystem(::Effekseer::COORDINATE_SYSTEM_RH);

  // �G�t�F�N�g�̓Ǎ�
  effect = Effekseer::Effect::Create(manager, (const EFK_CHAR*)(L"data/Effect/b_square.efk"));
  // �G�t�F�N�g�̍Đ�
  handle = manager->Play(effect,0,0,0);
}

//------------------------------------------------
// dtor
//------------------------------------------------
Test2::~Test2() {
  // �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
  ES_SAFE_RELEASE(effect);
  // �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
  manager->Destroy();
  // �`��p�C���X�^���X��j��
  renderer->Destory();
}

void Test2::Update() {
  //auto& camera = CameraManager::Instance().Find("MAIN_CAMERA");
  //const auto& proj = camera.GetProjectionMatrix();
  //const auto& view = camera.GetViewMatrix();
  //Effekseer::Matrix44 efk_view;
  //Effekseer::Matrix44 efk_proj;
  //for(int i = 0; i < 4; ++i) {
  //  for( int j = 0; j < 4; ++j ) {
  //    efk_view.Values[i][j] = view.m[i][j];
  //    efk_proj.Values[i][j] = proj.m[i][j];
  //  }
  //}

  //// ���e�s��̍X�V
  //renderer->SetProjectionMatrix(efk_proj);
  //// �J�����s��̍X�V
  //renderer->SetCameraMatrix(efk_view);
  //// 3D�T�E���h�p���X�i�[�ݒ�̍X�V
  ////sound->SetListener(���X�i�[�ʒu, ���ړ_, ������x�N�g��);
  //// �Đ����̃G�t�F�N�g�̈ړ���(::Effekseer::Manager�o�R�ŗl�X�ȃp�����[�^�[���ݒ�ł��܂��B)
  ////manager->AddLocation(handle, ::Effekseer::Vector3D);
  //// �S�ẴG�t�F�N�g�̍X�V
  //manager->Update();
}

void Test2::Draw() {
  renderer->BeginRendering();
  manager->Draw();
  renderer->EndRendering();
}