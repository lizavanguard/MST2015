//==============================================================================
//
// _TextureManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/SingletonHolder.hpp"

#include "Framework/Utility/DeviceHolder.h"
#include "Framework/Utility/GroupDataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _TextureManager {
private:
  using ContainerType = GroupDataLoader<LPDIRECT3DTEXTURE9>;
  using KeyType = ContainerType::KeyType;
  using DataFinderType = ContainerType::DataFinderType;

public:
  // ctor
  _TextureManager();

  // dtor
  ~_TextureManager();

  // Load
  // 大元のディレクトリに、サブのディレクトリを加えたパスのファイルをロードする
  // main = ./data/texture/
  // sub  = Title
  //  => ./data/texture/Title/
  void Load(const char* p_sub_directory_name);

  // Unload
  void Unload(const char* p_sub_directory_name);

  // find
  // SubDirectoryとファイル名をくっつけたやつ
  // ex) Title/texture000
  LPDIRECT3DTEXTURE9 Find(const KeyType& p_file_name) const;
  // find
  // SubDirectoryとファイル名を分けたやつ
  LPDIRECT3DTEXTURE9 Find(const KeyType& p_sub_directory_name, const DataFinderType::KeyType& p_file_name) const;

private:
  ContainerType* p_container_;
};

using TextureManager = liza::generic::SingletonHolder<_TextureManager>;
