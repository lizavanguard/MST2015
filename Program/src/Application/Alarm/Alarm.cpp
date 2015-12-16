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
  // �����Ă����
  for (auto data : data_) {
    for (auto p_listener : data.listener_list) {
      SafeDelete(p_listener);
    }
  }
}

//------------------------------------------------
// Update
// �S�Ẵf�[�^�̒ʒm���I����Ă���ꍇ��true���A��ł��c���Ă���ꍇ��false��Ԃ�
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
// �ŏ������蒼��
//------------------------------------------------
void Alarm::Reset(void) {
  current_index_ = 0;
  sum_time_ = 0.0f;
}

//------------------------------------------------
// Jump
// �w�肳�ꂽ�Ԗڂ̃f�[�^�܂Ŗ��������
// ���̍ۂɁA��΂��ꂽ�f�[�^�̒ʒm���X�g�͖��������
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
// ���݂̃C���f�b�N�X�̃��X�i�[�ɒʒm����
//------------------------------------------------
void Alarm::_Notify(void) {
  for (auto p_listener : data_[current_index_].listener_list) {
    p_listener->Notify();
  }
}
