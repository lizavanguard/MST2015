//==============================================================================
//
// DataLoader
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
// 色々書いたけど、そのまま使う時は、
//   ロードしたい型
//   データまでのパス
//   ロード関数
// を指定すれば良い
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <unordered_map>

#include "liza/generic/noncopyable.h"

#include "STL_Utility.h"
#include "_DataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<
  typename T,
  template<class> class DestroyPolicy = UsingRelease
>
class DataLoader : public liza::generic::NonCopyable<DataLoader<T, DestroyPolicy>> {
public:
  using KeyType = std::string;
  using DataType = T;
  using ContainerType = std::unordered_map<KeyType, DataType, std::hash<KeyType>, IgnoreCaseStringEqualTo>;
  using Iterator = typename ContainerType::iterator;
  using ConstIterator = typename ContainerType::const_iterator;

public:
  // ctor
  template<typename LoadFunction>
  DataLoader(const char* p_start_directory_path, LoadFunction load_function);

  // dtor
  ~DataLoader();

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

#include "DataLoader.inl"
