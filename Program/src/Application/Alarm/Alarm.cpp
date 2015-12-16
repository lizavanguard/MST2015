//==============================================================================
//
// Alarm
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Alarm.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Alarm::Alarm(DataContainerType data)
    : data_(data)
    , current_index_(0)
    , sum_time_(0.0f) {
  _Notify();
}

//------------------------------------------------
// dtor
//------------------------------------------------
Alarm::~Alarm() {
  // 消しているよ
  for (auto data : data_) {
    for (auto p_listener : data.listener_list) {
      SafeDelete(p_listener);
    }
  }
}

//------------------------------------------------
// Update
// 全てのデータの通知が終わっている場合はtrueを、一つでも残っている場合はfalseを返す
//------------------------------------------------
bool Alarm::Update(const float elapsed_time) {
  if (current_index_ >= data_.size()) {
    return true;
  }

  sum_time_ += elapsed_time;

  Data& data = data_[current_index_];
  if (sum_time_ >= data.time) {
    ++current_index_;
    sum_time_ = 0.0f;

    if (current_index_ >= data_.size()) {
      return true;
    }

    _Notify();
  }
  return false;
}

//------------------------------------------------
// Reset
// 最初からやり直し
//------------------------------------------------
void Alarm::Reset(void) {
  current_index_ = 0;
  sum_time_ = 0.0f;
}

//------------------------------------------------
// Jump
// 指定された番目のデータまで無理やり飛ぶ
// その際に、飛ばされたデータの通知リストは無視される
//------------------------------------------------
void Alarm::Jump(const unsigned int index) {
  if (current_index_ >= data_.size()) {
    return;
  }
  current_index_ = index;
  sum_time_ = 0.0f;

  _Notify();
}

//------------------------------------------------
// 現在のインデックスのリスナーに通知する
//------------------------------------------------
void Alarm::_Notify(void) {
  for (auto p_listener : data_[current_index_].listener_list) {
    p_listener->Notify();
  }
}
