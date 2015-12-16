//==============================================================================
//
// GroupDataLoader
// Author: Shimizu Shoji
//
// �ǂݍ��݊֐��̏���:
//   1. const char*
//   2. T*
// �������Ɏ�邱�Ƃł�
//
// �T�u�f�B���N�g���̎�O�܂ł̃p�X�𐶐����ɓn���āA
// �T�u�f�B���N�g���ȉ��̃��[�h���ɃT�u�f�B���N�g���̖��O�ƃ��[�h�֐����w�肷��Ύg����
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <unordered_map>

#include "DataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<
  typename T,
  template<class> class DestroyPolicy = UsingRelease
>
class GroupDataLoader {
public:
  using DataFinderType = DataLoader<T, DestroyPolicy>;
  using KeyType = typename DataFinderType::KeyType;
  using HashType = std::hash<KeyType>;
  using ContainerType = std::unordered_map<KeyType, DataFinderType*, HashType, IgnoreCaseStringEqualTo>;

public:
  // ctor
  GroupDataLoader(const char* p_main_directory_path);

  // dtor
  ~GroupDataLoader();

  // Load
  // �匳�̃f�B���N�g���ɁA�T�u�̃f�B���N�g�����������p�X�̃t�@�C�������[�h����
  // main = ./data/xxx/
  // sub  = Title
  //  => ./data/xxx/Title/
  template<typename LoadFunction>
  void Load(const char* p_sub_directory_name, LoadFunction load_function);

  // Unload
  void Unload(const char* p_sub_directory_name);

  // find
  // SubDirectory�ƃt�@�C�����������������
  // ex) Title/xxx000
  //     sub -> Title
  //    file -> xxx000
  T Find(const KeyType& p_file_name) const;

  // find
  // SubDirectory�ƃt�@�C�����𕪂������
  T Find(const KeyType& p_sub_directory_name, const KeyType& p_file_name) const;

  // find
  // �t�@�C���������H�������̂܂ܓn��
  T FindWithPureKey(const KeyType& p_file_name) const;

  // find
  // SubDirectory�ƃt�@�C�����𕪂������
  // �t�@�C���������H�������̂܂ܓn��
  T FindWithPureKey(const KeyType& p_sub_directory_name, const KeyType& p_file_name) const;

  // get
  DataFinderType* GetContainer(unsigned int index);
  unsigned int size(void) const;

private:
  ContainerType container_;
  std::string main_directory_path_;
};

#include "GroupDataLoader.inl"
