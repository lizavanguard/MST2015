//==============================================================================
//
// DataFinder
// Author: Shimizu Shoji
//
// 指定されたディレクトリ内のファイル名を読み込みます
// また、その際に指定された読み込み関数を用い、ファイル名からオブジェクトを生成します
// Policy)
//   Destroy Policy: 生成したオブジェクトの破棄クラス
//                   Destroy(T data)関数を提供すれば良い
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <map>

#include "_DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<
  typename T,
  template<class> class DestroyPolicy = UsingRelease
>
class DataFinder {
public:
  using KeyType = std::string;
  using DataType = T;
  using ContainerType = std::map<KeyType, DataType>;
  using LoadFunctionType = void(*)(const char* p_filename, T* p_data);

public:
  // ctor
  DataFinder(const char* p_start_directory_path, LoadFunctionType load_function);

  // dtor
  ~DataFinder();

  // find data
  T Find(const KeyType& key) const;

private:
  // property
  ContainerType container_;
};

#include "DataFinder.inl"
