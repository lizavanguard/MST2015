//==============================================================================
//
// SimpleTimer
// Author: Shimizu Shoji
//
// 基本的なタイマー
// 1 => 1s, 0.001 => 1ms
// スタート時からの経過時間をカウントする
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
namespace utility {

// 詳細はファイルヘッダを参照
class SimpleTimer {
public:
  // ctor
  // タイマーの通知間隔を設定する
  SimpleTimer();

  // 経過時間を更新し、返す
  float Update(void);

  // Reset
  void Reset(void);

private:
  float _GetTime(void) const;

  float start_time_;
};

}  // namespace utility
}  // namespace liza

// inline
#include "SimpleTimer.inl"
