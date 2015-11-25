//==============================================================================
//
// HUDモジュール [HudOverlay.cpp]
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
  // 頂点バッファの確保
  auto p_device = DeviceHolder::Instance().GetDevice();
  p_device->CreateVertexBuffer(
    sizeof(Vertex2Standard) * kNumVertex,
    D3DUSAGE_WRITEONLY,
    Vertex2Standard::VertexDeclType,
    D3DPOOL_MANAGED,
    &pVertexBuffer_,
    nullptr);

  // 対角線の長さを算出
  _UpdateDiagonalLength();

  // 中心点から対角線への角度の算出
  _UpdateAngle();

  // 長さの算出
  float distX = sinf(rot_ + angle_) * length_;
  float distY = cosf(rot_ + angle_) * length_;

  // 頂点情報の設定
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // 座標の設定
  // 左上
  pVertex[0].vtx.x = pos_.x - distX;
  pVertex[0].vtx.y = pos_.y - distY;
  pVertex[0].vtx.z = 0;

  // 右上
  pVertex[1].vtx.x = pos_.x + distX;
  pVertex[1].vtx.y = pos_.y - distY;
  pVertex[1].vtx.z = 0;

  // 左下
  pVertex[2].vtx.x = pos_.x - distX;
  pVertex[2].vtx.y = pos_.y + distY;
  pVertex[2].vtx.z = 0;

  // 右下
  pVertex[3].vtx.x = pos_.x + distX;
  pVertex[3].vtx.y = pos_.y + distY;
  pVertex[3].vtx.z = 0;

  // rhwの設定
  pVertex[0].rhw = 1.0f;
  pVertex[1].rhw = 1.0f;
  pVertex[2].rhw = 1.0f;
  pVertex[3].rhw = 1.0f;

  // 反射光の設定
  pVertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
  pVertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

  // テクスチャ座標の設定
  pVertex[0].tex = Vector2(0.0f, 0.0f);
  pVertex[1].tex = Vector2(1.0f, 0.0f);
  pVertex[2].tex = Vector2(0.0f, 1.0f);
  pVertex[3].tex = Vector2(1.0f, 1.0f);

  // 占有終了
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// dtor
//------------------------------------------------
HudOverlay::~HudOverlay() {
  SafeRelease(pVertexBuffer_);
}


//------------------------------------------------
// 描画処理
//------------------------------------------------
void HudOverlay::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_device->SetStreamSource(0, pVertexBuffer_, 0, sizeof(Vertex2Standard));
  p_device->SetFVF(Vertex2Standard::VertexDeclType);

  p_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//------------------------------------------------
// アルファの変更
// 0~1の範囲で設定してください
//------------------------------------------------
void HudOverlay::ChangeAlpha(const float a) {
  // 占有開始
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // 反射光の設定
  // 反射光の設定
  for (int vertex_cnt = 0; vertex_cnt < kNumVertex; ++vertex_cnt) {
    DWORD work = pVertex[vertex_cnt].diffuse;
    pVertex[vertex_cnt].diffuse = D3DCOLOR_RGBA((work & 0xff) >> 16, (work & 0xff) >> 8, (work & 0xff), (DWORD)(a*255.f));
  }

  // 占有終了
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// 色の変更
// 0~1の範囲で設定してください
//------------------------------------------------
void HudOverlay::ChangeColor(const D3DXVECTOR4& color) {
  // 占有開始
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // 反射光の設定
  for (int vertex_cnt = 0; vertex_cnt < kNumVertex; ++vertex_cnt) {
    pVertex[vertex_cnt].diffuse = D3DCOLOR_RGBA((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255));
  }

  // 占有終了
  pVertexBuffer_->Unlock();
}


void HudOverlay::ChangeColor(const float r, const float g, const float b, const float a) {
  ChangeColor(D3DXVECTOR4(r, g, b, a));
}


//------------------------------------------------
// uv値の変更
//------------------------------------------------
void HudOverlay::ChangeUV(
  const float su, const float eu,
  const float sv, const float ev
  ) {
  // 占有開始
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // テクスチャ座標の設定
  pVertex[0].tex = Vector2(su, sv);
  pVertex[1].tex = Vector2(eu, sv);
  pVertex[2].tex = Vector2(su, ev);
  pVertex[3].tex = Vector2(eu, ev);

  // 占有終了
  pVertexBuffer_->Unlock();
}


//------------------------------------------------
// 全てを更新
//------------------------------------------------
void HudOverlay::_UpdateAll(void) {
  _UpdateAngle();
  _UpdateDiagonalLength();
  _UpdatePos();
}


//------------------------------------------------
// 角度を計算
//------------------------------------------------
void HudOverlay::_UpdateAngle(void) {
  angle_ = atan2f(size_.x, size_.y);
}


//------------------------------------------------
// 対角線の長さを計算
//------------------------------------------------
void HudOverlay::_UpdateDiagonalLength(void) {
  float halfX = size_.x / 2.0f;
  float halfY = size_.y / 2.0f;

  // 対角線の長さを求める
  length_ = sqrtf((halfX * halfX) + (halfY * halfY));
}


//------------------------------------------------
// 座標の更新
//------------------------------------------------
void HudOverlay::_UpdatePos(void) {
  float distX = sinf(rot_ + angle_) * length_;
  float distY = cosf(rot_ + angle_) * length_;

  // 頂点情報の設定
  Vertex2Standard* pVertex = nullptr;
  pVertexBuffer_->Lock(0, 0, (void**)&pVertex, 0);

  // 座標の設定
  // 左上
  pVertex[0].vtx.x = pos_.x - distX;
  pVertex[0].vtx.y = pos_.y - distY;

  // 右上
  pVertex[1].vtx.x = pos_.x + distX;
  pVertex[1].vtx.y = pos_.y - distY;

  // 左下
  pVertex[2].vtx.x = pos_.x - distX;
  pVertex[2].vtx.y = pos_.y + distY;

  // 右下
  pVertex[3].vtx.x = pos_.x + distX;
  pVertex[3].vtx.y = pos_.y + distY;

  // 占有終了
  pVertexBuffer_->Unlock();
}