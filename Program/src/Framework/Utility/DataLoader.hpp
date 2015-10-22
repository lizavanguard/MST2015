//==============================================================================
//
// DataLoader
// Author: Shimizu Shoji
//
// �w�肳�ꂽ�f�B���N�g�����̃t�@�C������ǂݍ��݂܂�
// �܂��A���̍ۂɎw�肳�ꂽ�ǂݍ��݊֐���p���A�t�@�C��������I�u�W�F�N�g�𐶐����܂�
//
// �ǂݍ��݊֐��̏���:
//   1. const char*
//   2. T*
// �������Ɏ�邱�Ƃł�
//
// Policy�N���X�̐���:
//   Destroy Policy: ���������I�u�W�F�N�g�̔j���N���X
//                   Destroy(T data)�֐���񋟂���Ηǂ�
//
// �F�X���������ǁA���̂܂܎g�����́A
//   ���[�h�������^
//   �f�[�^�܂ł̃p�X
//   ���[�h�֐�
// ���w�肷��Ηǂ�
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
