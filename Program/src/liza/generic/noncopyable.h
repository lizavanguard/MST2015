//==============================================================================
//
// コピー/代入禁止インタフェース
// Author : Shimizu Shoji
//
// コピーと代入を禁止するためのインタフェースです。
// このクラスをpublic継承してください。
// static_assert とか入れたほうが親切かも
//
//==============================================================================
#pragma once
#ifndef __H_LIZA_GENERIC_NONCOPYABLE_H__
#define __H_LIZA_GENERIC_NONCOPYABLE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
namespace generic {

// 詳しくはファイルヘッダにて説明。
template<class T>
class NonCopyable {
protected:
  NonCopyable() {}
  ~NonCopyable() {}

private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable &);
  //T& operator=(const T &);  // これだとコピーできてしまう
};

}  // namespace generic
}  // namespace liza

#endif  // __H_LIZA_GENERIC_NONCOPYABLE_H__
