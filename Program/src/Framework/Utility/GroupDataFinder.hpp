//==============================================================================
//
// GroupDataFinder
// Author: Shimizu Shoji
//
// 読み込み関数の条件:
//   1. const char*
//   2. T*
// を引数に取ることです
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <unordered_map>
#include "DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<
  typename T,
  template<class> class DestroyPolicy = UsingRelease
>
class GroupDataFinder {
public:
  using DataFinderType = DataFinder<T, DestroyPolicy>;
  using KeyType = typename DataFinderType::KeyType;
  using ContainerType = std::unordered_map<KeyType, DataFinderType*>;

public:
  // ctor
  GroupDataFinder(const char* p_main_directory_path);

  // dtor
  ~GroupDataFinder();

  // Load
  // 大元のディレクトリに、サブのディレクトリを加えたパスのファイルをロードする
  // main = ./data/xxx/
  // sub  = Title
  //  => ./data/xxx/Title/
  template<typename LoadFunction>
  void Load(const char* p_sub_directory_name, LoadFunction load_function);

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
  std::string main_directory_path_;
};

#include "GroupDataFinder.inl"
