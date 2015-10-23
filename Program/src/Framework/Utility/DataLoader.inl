//==============================================================================
//
// DataLoader
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "DataLoader.hpp"

//==============================================================================
// function impl
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
template<typename LoadFunction>
DataLoader<T, DestroyPolicy>::DataLoader(const char* p_start_directory_path, LoadFunction load_function) {
  std::string file_path = p_start_directory_path;
  file_path += "/*.*";  // 全部

  // open
  WIN32_FIND_DATA find_data;
  HANDLE h_find = FindFirstFile(file_path.c_str(), &find_data);
  MY_BREAK_ASSERTMSG(h_find != INVALID_HANDLE_VALUE, "ディレクトリが開きませんでした");
  if (h_find == INVALID_HANDLE_VALUE) {
    return;
  }

  // 変なファイル削除用
  FindNextFile(h_find, &find_data);

  // ディレクトリを全て回す
  while (FindNextFile(h_find, &find_data)) {
    file_path = p_start_directory_path;
    file_path += '/';
    file_path += find_data.cFileName;
    // Thumbs.dbを飛ばす
    if (std::string(find_data.cFileName) == "Thumbs.db") {
      continue;
    }

    T p_data = nullptr;
    load_function(file_path.c_str(), &p_data);
    MY_BREAK_NULL_ASSERT(p_data);
    if (!p_data) {
      return;
    }

    // 拡張子を消す(拡張子がないファイルは考慮していない)
    std::string file_name = find_data.cFileName;
    //for (int char_index = file_name.size(); char_index > 0; --char_index) {
    //  if (file_name[char_index - 1] == '.') {
    //    file_name.pop_back();
    //    break;
    //  }
    //  file_name.pop_back();
    //}
    std::string data_name = DeleteExtension(file_name);

    // 登録
    container_.insert(std::make_pair(data_name, p_data));
  }

  // close
  FindClose(h_find);
}

//------------------------------------------------
// dtor
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
DataLoader<T, DestroyPolicy>::~DataLoader() {
  for (auto it = container_.begin(); it != container_.end();) {
    DestroyPolicy<T>::Destroy(it->second);
    it = container_.erase(it);
  }
}

//------------------------------------------------
// find data
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
T DataLoader<T, DestroyPolicy>::Find(const KeyType& key) const {
  return FindWithPureKey(DeleteExtension(key.c_str()));
}

//------------------------------------------------
// find data with extension
//------------------------------------------------
template<
  typename T,
  template<class> class DestroyPolicy
>
T DataLoader<T, DestroyPolicy>::FindWithPureKey(const KeyType& key) const {
  auto it = container_.find(key);
  MY_BREAK_ASSERTMSG(it != container_.end(), "データがありませんでした");
  if (it == container_.end()) {
    return nullptr;
  }
  return it->second;
}
