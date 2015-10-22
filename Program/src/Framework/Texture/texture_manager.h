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
  // �匳�̃f�B���N�g���ɁA�T�u�̃f�B���N�g�����������p�X�̃t�@�C�������[�h����
  // main = ./data/texture/
  // sub  = Title
  //  => ./data/texture/Title/
  void Load(const char* p_sub_directory_name);

  // Unload
  void Unload(const char* p_sub_directory_name);

  // find
  // SubDirectory�ƃt�@�C�����������������
  // ex) Title/texture000
  LPDIRECT3DTEXTURE9 Find(const KeyType& p_file_name) const;
  // find
  // SubDirectory�ƃt�@�C�����𕪂������
  LPDIRECT3DTEXTURE9 Find(const KeyType& p_sub_directory_name, const DataFinderType::KeyType& p_file_name) const;

private:
  ContainerType* p_container_;
};

using TextureManager = liza::generic::SingletonHolder<_TextureManager>;
