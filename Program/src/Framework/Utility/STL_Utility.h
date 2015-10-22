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
// �������A�啶���̈Ⴂ�𖳎����Ĕ�����s���֐��I�u�W�F�N�g
// ex)
// FooBar == foobar
//------------------------------------------------
struct IgnoreCaseStringEqualTo : public std::binary_function<std::string, std::string, bool> {
  bool operator()(const std::string& lhs, const std::string& rhs) const {
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), [](char lhs, char rhs) {
      return tolower(lhs) == tolower(rhs); });
  }
};
