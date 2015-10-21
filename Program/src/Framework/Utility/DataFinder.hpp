//==============================================================================
//
// DataFinder
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <map>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
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
  T Find(const KeyType& key);

private:
  // property
  ContainerType container_;
};

#include "DataFinder.inl"
