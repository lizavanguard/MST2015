//==============================================================================
//
// Alarm
// Author: Shimizu Shoji
//
// 時間と通知リストからなるデータのリストを保持する
// 流れとしては、初期化時に最初のデータの通知リストに対して通知を行う。
// 次に、最初のデータで指定された時間の経過後に、二番目のデータの通知リスト全体に対して通知を行う。
// 続いて、二番目のデータで指定された時間の経過後に、三番目のデータの通知リスト全体に対して通知を行う。
// 以下を繰り返し、最後のデータになるまで行う。
//
// 時間は次のデータに移行するまでの時間を格納する。
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <list>
#include <vector>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// ヘッダを参照
class Alarm {
public:
  // inner class
  class Listener {
  public:
    // ctor/dtor
    Listener() {}
    virtual ~Listener() {}

    // Notify
    virtual void Notify(void) = 0;
  };

  // struct
  struct Data {
    std::list<Listener*> listener_list;
    float time;
  };

  // alias
  using DataContainerType = std::vector<Data>;

public:
  // ctor
  Alarm(DataContainerType data);

  // dtor
  ~Alarm();

  // Update
  // 全てのデータの通知が終わっている場合はtrueを、一つでも残っている場合はfalseを返す
  bool Update(float elapsed_time);

  // Reset
  // 最初からやり直し
  void Reset(void);

  // Jump
  // 指定された番目のデータまで無理やり飛ぶ
  // その際に、飛ばされたデータの通知リストは無視される
  void Jump(unsigned int data);

  // get
  unsigned int GetCurrentDataIndex(void) const { return current_index_; }

private:
  // _function
  void _Notify(void);

  // property
  DataContainerType data_;
  unsigned int current_index_;
  float sum_time_;  // データの通知が行われる度にリセットされる
};
