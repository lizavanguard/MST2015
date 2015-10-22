//==============================================================================
//
// GroupDataFinder
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <map>
#include "DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
class GroupDataFinder {
public:
  using DataFinderType = DataFinder<T>;
  using KeyType = typename DataFinderType::KeyType;
  using ContainerType = std::map<KeyType, DataFinderType*>;
  using LoadFunctionType = typename DataFinderType::LoadFunctionType;

public:
  // ctor
  GroupDataFinder(const char* p_main_directory_path, LoadFunctionType load_function);

  // dtor
  ~GroupDataFinder();

  // Load
  // 大元のディレクトリに、サブのディレクトリを加えたパスのファイルをロードする
  // main = ./data/xxx/
  // sub  = Title
  //  => ./data/xxx/Title/
  void Load(const char* p_sub_directory_name);

  // Unload
  void Unload(const char* p_sub_directory_name);

  // find
  // SubDirectoryとファイル名をくっつけたやつ
  // ex) Title/xxx000
  //     sub -> Title
  //    file -> xxx000
  T Find(const KeyType& p_file_name) const;

  // find
  // SubDirectoryとファイル名を分けたやつ
  T Find(const KeyType& p_sub_directory_name, const KeyType& p_file_name) const;

private:
  ContainerType container_;
  LoadFunctionType load_function_;
  std::string main_directory_path_;
};

#include "GroupDataFinder.inl"
