//=========================================o=====================================
//
// DirectX用ユーティリティ
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZA_GAME_DIRECTX_UTILITY_H__
#define __H_LIZA_GAME_DIRECTX_UTILITY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <d3dx9.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
namespace game {
namespace directx {

//------------------------------------------------
// シェーダのロードを行う
// ポインタを渡すと格納して戻す
//------------------------------------------------
void LoadShader(LPDIRECT3DDEVICE9 p_device, const char* p_filename, LPD3DXEFFECT* pp_effect);

//------------------------------------------------
// メッシュのロードを行う
// 内部で最適化も行う
//------------------------------------------------
void LoadMeshFromX(
    LPDIRECT3DDEVICE9 p_device,
    const char* p_filename,
    LPD3DXMESH* pp_mesh,
    LPD3DXBUFFER* pp_material,
    DWORD* p_num_material);

//------------------------------------------------
// メッシュに頂点宣言の情報を埋め込む
//------------------------------------------------
void AttachVertexDeclarationToMesh(
    LPDIRECT3DDEVICE9 p_device,
    LPD3DXMESH* pp_mesh,
    D3DVERTEXELEMENT9* p_elements);

//------------------------------------------------
// デバッグ用関数
// 中身を確認したいテクスチャを渡す
// 描画する場合は、確認したい全てのテクスチャを渡した後に
// 対応した描画関数を呼ぶ
//------------------------------------------------
void AddTextureDebug(LPDIRECT3DTEXTURE9 p_texture);

//------------------------------------------------
// デバッグ用関数
// 対応する追加関数により渡されたテクスチャを画面左上に描画する
// 渡された順番に左上から左下に並べて描画される
//------------------------------------------------
void DrawTextureDebug(LPDIRECT3DDEVICE9 p_device);

}  // namespace directx
}  // namespace game
}  // liza

// inline header
#include "utility.inl"

#endif // __H_LIZA_GAME_DIRECTX_UTILITY_H__
