//==============================================================================
//
// DataFinder
// Author: Shimizu Shoji
//
// 指定されたディレクトリ内のファイル名を読み込みます
// また、その際に指定された読み込み関数を用い、ファイル名からオブジェクトを生成します
//
// 読み込み関数の条件:
//   1. const char*
//   2. T*
// を引数に取ることです
//
// Policyクラスの説明:
//   Destroy Policy: 生成したオブジェクトの破棄クラス
//                   Destroy(T data)関数を提供すれば良い
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <unordered_map>

#include "liza/generic/noncopyable.h"

#include "_DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<
  typename T,
  template<class> class DestroyPolicy = UsingRelease
>
class DataFinder : public liza::generic::NonCopyable<DataFinder<T, DestroyPolicy>> {
public:
  using KeyType = std::string;
  using DataType = T;
  using ContainerType = std::unordered_map<KeyType, DataType>;
  using Iterator = typename ContainerType::iterator;
  using ConstIterator = typename ContainerType::const_iterator;

public:
  // ctor
  template<typename LoadFunction>
  DataFinder(const char* p_start_directory_path, LoadFunction load_function);

  // dtor
  ~DataFinder();

  // find data
  T Find(const KeyType& key) const;

  Iterator begin(void) { return container_.begin(); }
  ConstIterator begin(void) const { return container_.begin(); }
  Iterator end(void) { return container_.end(); }
  ConstIterator end(void) const { return container_.end(); }


private:
  // property
  ContainerType container_;
};

#include "DataFinder.inl"
