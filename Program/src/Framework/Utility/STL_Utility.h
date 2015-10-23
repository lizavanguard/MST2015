//==============================================================================
//
// STL Utility
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <functional>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//------------------------------------------------
// 拡張子を消す(最後の.以降を消す)
// 拡張子がないなら何もしない
//------------------------------------------------
inline std::string DeleteExtension(const std::string& src) {
  std::string::size_type index = src.rfind('.');
  if (index == 0) {
    return src;
  }
  return std::string(src, 0, src.rfind('.'));
}

//------------------------------------------------
// 小文字、大文字の違いを無視して判定を行う関数オブジェクト
// ex)
// FooBar == foobar
//------------------------------------------------
struct IgnoreCaseStringEqualTo : public std::binary_function<std::string, std::string, bool> {
  bool operator()(const std::string& lhs, const std::string& rhs) const {
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), [](char lhs, char rhs) {
      return tolower(lhs) == tolower(rhs); });
  }
};
