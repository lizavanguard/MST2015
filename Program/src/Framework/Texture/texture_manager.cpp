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
_TextureManager::_TextureManager() {
}

//------------------------------------------------
// dtor
//------------------------------------------------
_TextureManager::~_TextureManager() {
  for (auto it = container_.begin(); it != container_.end();) {
    SafeDelete(it->second);
    it = container_.erase(it);
  }
}

//------------------------------------------------
// Load
// 大元のディレクトリに、サブのディレクトリを加えたパスのファイルをロードする
// main = ./data/texture/
// sub  = Title
//  => ./data/texture/Title/
//------------------------------------------------
void _TextureManager::Load(const char* p_sub_directory_name) {
  static const char* kMainDirectoryPath = "./data/Texture/";
  std::string data_path = kMainDirectoryPath;
  data_path += p_sub_directory_name;
  data_path += "/";
  DataFinderType* p_finder = new DataFinderType(data_path.c_str(), [](const char* p_filename, LPDIRECT3DTEXTURE9* pp_texture) {
    D3DXCreateTextureFromFile(DeviceHolder::Instance().GetDevice(), p_filename, pp_texture);});

  container_.insert(std::make_pair(p_sub_directory_name, p_finder));
}

//------------------------------------------------
// Unload
//------------------------------------------------
void _TextureManager::Unload(const char* p_sub_directory_name) {
  auto it = container_.find(p_sub_directory_name);
  if (it == container_.end()) {
    return;
  }
  SafeDelete(it->second);
}

//------------------------------------------------
// find
// SubDirectoryとファイル名をくっつけたやつ
//------------------------------------------------
LPDIRECT3DTEXTURE9 _TextureManager::Find(const DataFinderType::KeyType& p_file_name) const {
  std::string work = p_file_name;

  MY_BREAK_ASSERTMSG(work.size() >= 3, "不正な文字列が入っています");
  if (work.size() < 3) {
    return nullptr;
  }

  for (unsigned int char_index = 0; char_index < work.size(); ++char_index) {
    if (work[char_index] != '/') {
      continue;
    }

    std::string file_name(work.substr(char_index + 1));
    std::string sub_directory_name(work, 0, char_index);
    return Find(sub_directory_name, file_name);
  }

  return nullptr;
}

//------------------------------------------------
// find
// SubDirectoryとファイル名を分けたやつ
//------------------------------------------------
LPDIRECT3DTEXTURE9 _TextureManager::Find(const KeyType& p_sub_directory_name, const DataFinderType::KeyType& p_file_name) const {
  auto it = container_.find(p_sub_directory_name);
  if (it == container_.end()) {
    return nullptr;
  }

  return it->second->Find(p_file_name);
}
