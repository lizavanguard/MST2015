//==============================================================================
//
// HUD���W���[�� [HudOverlay.cpp]
// Designed On 2014.02.04 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "HudOverlay.h"

#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Utility/Vertex2Standard.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
  const int kNumVertex = 4;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
HudOverlay::HudOverlay(const Vector2& pos, float rot, const Vector2& size)
  : pVertexBuffer_(nullptr)
  , pos_(pos)
  , rot_(rot)
  , size_(size)
  , length_(0)
  , angle_(0)
{
  // ���_�o�b�t�@�̊m��
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateVertexBuffer(
    sizeof(Vertex2Standard) * kNumVertex,
    D3DUSAGE_WRITEONLY,
    Vertex2Standard::VertexDeclType,
    D3DPOOL_MANAGED,
    &pVertexBuffer_,
    nullptr);

  // �Ίp���̒������Z�o
  _UpdateDiagonalLength();

  // ���S�_����Ίp���ւ̊p�x�̎Z�o
  _UpdateAngle();

  // �����̎Z�o
  float distX = sinf(rot_ + angle_) * length_;
  float distY = cosf(rot_ + angle_) * length_;

  // ���_���̐ݒ�
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // ���W�̐ݒ�
  // ����
  pVertex[0].vtx.x = pos_.x - distX;
  pVertex[0].vtx.y = pos_.y - distY;
  pVertex[0].vtx.z = 0;

  // �E��
  pVertex[1].vtx.x = pos_.x + distX;
  pVertex[1].vtx.y = pos_.y - distY;
  pVertex[1].vtx.z = 0;

  // ����
  pVertex[2].vtx.x = pos_.x - distX;
  pVertex[2].vtx.y = pos_.y + distY;
  pVertex[2].vtx.z = 0;

  // �E��
  pVertex[3].vtx.x = pos_.x + distX;
  pVertex[3].vtx.y = pos_.y + distY;
  pVertex[3].vtx.z = 0;

  // rhw�̐ݒ�
  pVertex[0].rhw = 1.0f;
  pVertex[1].rhw = 1.0f;
  pVertex[2].rhw = 1.0f;
  pVertex[3].rhw = 1.0f;

  // ���ˌ��̐ݒ�
  pVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

  // �e�N�X�`�����W�̐ݒ�
  pVertex[0].tex = Vector2(0.0f, 0.0f);
  pVertex[1].tex = Vector2(1.0f, 0.0f);
  pVertex[2].tex = Vector2(0.0f, 1.0f);
  pVertex[3].tex = Vector2(1.0f, 1.0f);

  // ��L�I��
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// dtor
//------------------------------------------------
HudOverlay::~HudOverlay() {
  SafeRelease(pVertexBuffer_);
}


//------------------------------------------------
// �`�揈��
//------------------------------------------------
void HudOverlay::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_device->SetStreamSource(0, pVertexBuffer_, 0, sizeof(Vertex2Standard));
  p_device->SetFVF(Vertex2Standard::VertexDeclType);

  p_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//------------------------------------------------
// �A���t�@�̕ύX
// 0~1�͈̔͂Őݒ肵�Ă�������
//------------------------------------------------
void HudOverlay::ChangeAlpha(const float a) {
  // ��L�J�n
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // ���ˌ��̐ݒ�
  // ���ˌ��̐ݒ�
  for (int vertex_cnt = 0; vertex_cnt < kNumVertex; ++vertex_cnt) {
    DWORD work = pVertex[vertex_cnt].diffuse;
    pVertex[vertex_cnt].diffuse = D3DCOLOR_RGBA((work & 0xff) >> 16, (work & 0xff) >> 8, (work & 0xff), (DWORD)(a*255.f));
  }

  // ��L�I��
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// �F�̕ύX
// 0~1�͈̔͂Őݒ肵�Ă�������
//------------------------------------------------
void HudOverlay::ChangeColor(const D3DXVECTOR4& color) {
  // ��L�J�n
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // ���ˌ��̐ݒ�
  for (int vertex_cnt = 0; vertex_cnt < kNumVertex; ++vertex_cnt) {
    pVertex[vertex_cnt].diffuse = D3DCOLOR_RGBA((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255));
  }

  // ��L�I��
  pVertexBuffer_->Unlock();
}


void HudOverlay::ChangeColor(const float r, const float g, const float b, const float a) {
  ChangeColor(D3DXVECTOR4(r, g, b, a));
}


//------------------------------------------------
// uv�l�̕ύX
//------------------------------------------------
void HudOverlay::ChangeUV(
  const float su, const float eu,
  const float sv, const float ev
  ) {
  // ��L�J�n
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // �e�N�X�`�����W�̐ݒ�
  pVertex[0].tex = Vector2(su, sv);
  pVertex[1].tex = Vector2(eu, sv);
  pVertex[2].tex = Vector2(su, ev);
  pVertex[3].tex = Vector2(eu, ev);

  // ��L�I��
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// �S�Ă��X�V
//------------------------------------------------
void HudOverlay::_UpdateAll(void) {
  _UpdateAngle();
  _UpdateDiagonalLength();
  _UpdatePos();
}


//------------------------------------------------
// �p�x���v�Z
//------------------------------------------------
void HudOverlay::_UpdateAngle(void) {
  angle_ = atan2f(size_.x, size_.y);
}


//------------------------------------------------
// �Ίp���̒������v�Z
//------------------------------------------------
void HudOverlay::_UpdateDiagonalLength(void) {
  float halfX = size_.x / 2.0f;
  float halfY = size_.y / 2.0f;

  // �Ίp���̒��������߂�
  length_ = sqrtf((halfX * halfX) + (halfY * halfY));
}


//------------------------------------------------
// ���W�̍X�V
//------------------------------------------------
void HudOverlay::_UpdatePos(void) {
  float distX = sinf(rot_ + angle_) * length_;
  float distY = cosf(rot_ + angle_) * length_;

  // ���_���̐ݒ�
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // ���W�̐ݒ�
  // ����
  pVertex[0].vtx.x = pos_.x - distX;
  pVertex[0].vtx.y = pos_.y - distY;

  // �E��
  pVertex[1].vtx.x = pos_.x + distX;
  pVertex[1].vtx.y = pos_.y - distY;

  // ����
  pVertex[2].vtx.x = pos_.x - distX;
  pVertex[2].vtx.y = pos_.y + distY;

  // �E��
  pVertex[3].vtx.x = pos_.x + distX;
  pVertex[3].vtx.y = pos_.y + distY;

  // ��L�I��
  pVertexBuffer_->Unlock();
}