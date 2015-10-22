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
#include "GroupDataFinder.hpp"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
GroupDataFinder<T, DestroyPolicy>::GroupDataFinder(const char* p_main_directory_path)
    : main_directory_path_(p_main_directory_path) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
GroupDataFinder<T, DestroyPolicy>::~GroupDataFinder() {
  for (auto it = container_.begin(); it != container_.end();) {
    SafeDelete(it->second);
    it = container_.erase(it);
  }
}

//------------------------------------------------
// Load
// �匳�̃f�B���N�g���ɁA�T�u�̃f�B���N�g�����������p�X�̃t�@�C�������[�h����
// main = ./data/texture/
// sub  = Title
//  => ./data/texture/Title/
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
template<typename LoadFunction>
void GroupDataFinder<T, DestroyPolicy>::Load(const char* p_sub_directory_name, LoadFunction load_function) {
  std::string data_path = main_directory_path_;
  data_path += p_sub_directory_name;
  data_path += "/";
  DataFinderType* p_finder = new DataFinderType(data_path.c_str(), load_function);

  container_.insert(std::make_pair(p_sub_directory_name, p_finder));
}

//------------------------------------------------
// Unload
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
void GroupDataFinder<T, DestroyPolicy>::Unload(const char* p_sub_directory_name) {
  auto it = container_.find(p_sub_directory_name);
  if (it == container_.end()) {
    return;
  }
  SafeDelete(it->second);
}

//------------------------------------------------
// find
// SubDirectory�ƃt�@�C�����������������
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
T GroupDataFinder<T, DestroyPolicy>::Find(const KeyType& p_file_name) const {
  std::string work = p_file_name;

  MY_BREAK_ASSERTMSG(work.size() >= 3, "�s���ȕ����񂪓����Ă��܂�");
  if (work.size() < 3) {
    return nullptr;
  }

  for (unsigned int char_index = 0; char_index < work.size(); ++char_index) {
    if (work[char_index] != '/') {
      continue;
    }

    std::string file_name(work.substr(char_index + 1));
    std::string sub_directory_name(work, 0, char_index);
    return Find(sub_directory_name, file_name);
  }

  return nullptr;
}

//------------------------------------------------
// find
// SubDirectory�ƃt�@�C�����𕪂������
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
T GroupDataFinder<T, DestroyPolicy>::Find(const KeyType& p_sub_directory_name, const KeyType& p_file_name) const {
  auto it = container_.find(p_sub_directory_name);
  if (it == container_.end()) {
    return nullptr;
  }

  return it->second->Find(p_file_name);
}
