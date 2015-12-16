//==============================================================================
//
// GroupDataLoader
// Author: Shimizu Shoji
//
// 読み込み関数の条件:
//   1. const char*
//   2. T*
// を引数に取ることです
//
// サブディレクトリの手前までのパスを生成時に渡して、
// サブディレクトリ以下のロード時にサブディレクトリの名前とロード関数を指定すれば使える
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

  // find
  // ファイル名を加工せずそのまま渡す
  T FindWithPureKey(const KeyType& p_file_name) const;

  // find
  // SubDirectoryとファイル名を分けたやつ
  // ファイル名を加工せずそのまま渡す
  T FindWithPureKey(const KeyType& p_sub_directory_name, const KeyType& p_file_name) const;

  // get
  DataFinderType* GetContainer(unsigned int index);
  unsigned int size(void) const;

private:
  ContainerType container_;
  std::string main_directory_path_;
};

#include "GroupDataLoader.inl"
