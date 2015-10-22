//==============================================================================
//
// DataFinder
// Author: Shimizu Shoji
//
// �w�肳�ꂽ�f�B���N�g�����̃t�@�C������ǂݍ��݂܂�
// �܂��A���̍ۂɎw�肳�ꂽ�ǂݍ��݊֐���p���A�t�@�C��������I�u�W�F�N�g�𐶐����܂�
// Policy)
//   Destroy Policy: ���������I�u�W�F�N�g�̔j���N���X
//                   Destroy(T data)�֐���񋟂���Ηǂ�
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
