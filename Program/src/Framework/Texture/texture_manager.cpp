//==============================================================================
//
// _TextureManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "texture_manager.h"

#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_TextureManager::_TextureManager() : p_container_(nullptr) {
  static const char* kMainDirectoryPath = "./data/Texture/";
  p_container_ = new ContainerType(kMainDirectoryPath, [](const char* p_filename, LPDIRECT3DTEXTURE9* pp_texture) {
    D3DXCreateTextureFromFile(DeviceHolder::Instance().GetDevice(), p_filename, pp_texture); });
}

//------------------------------------------------
// dtor
//------------------------------------------------
_TextureManager::~_TextureManager() {
  SafeDelete(p_container_);
}

//------------------------------------------------
// Load
// 大元のディレクトリに、サブのディレクトリを加えたパスのファイルをロードする
// main = ./data/texture/
// sub  = Title
//  => ./data/texture/Title/
//------------------------------------------------
void _TextureManager::Load(const char* p_sub_directory_name) {
  p_container_->Load(p_sub_directory_name);
}

//------------------------------------------------
// Unload
//------------------------------------------------
void _TextureManager::Unload(const char* p_sub_directory_name) {
  p_container_->Unload(p_sub_directory_name);
}

//------------------------------------------------
// find
// SubDirectoryとファイル名をくっつけたやつ
//------------------------------------------------
LPDIRECT3DTEXTURE9 _TextureManager::Find(const DataFinderType::KeyType& p_file_name) const {
  return p_container_->Find(p_file_name);
}

//------------------------------------------------
// find
// SubDirectoryとファイル名を分けたやつ
//------------------------------------------------
LPDIRECT3DTEXTURE9 _TextureManager::Find(const KeyType& p_sub_directory_name, const DataFinderType::KeyType& p_file_name) const {
  return p_container_->Find(p_sub_directory_name, p_file_name);
}
