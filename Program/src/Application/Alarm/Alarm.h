//==============================================================================
//
// Alarm
// Author: Shimizu Shoji
//
// ���Ԃƒʒm���X�g����Ȃ�f�[�^�̃��X�g��ێ�����
// ����Ƃ��ẮA���������ɍŏ��̃f�[�^�̒ʒm���X�g�ɑ΂��Ēʒm���s���B
// ���ɁA�ŏ��̃f�[�^�Ŏw�肳�ꂽ���Ԃ̌o�ߌ�ɁA��Ԗڂ̃f�[�^�̒ʒm���X�g�S�̂ɑ΂��Ēʒm���s���B
// �����āA��Ԗڂ̃f�[�^�Ŏw�肳�ꂽ���Ԃ̌o�ߌ�ɁA�O�Ԗڂ̃f�[�^�̒ʒm���X�g�S�̂ɑ΂��Ēʒm���s���B
// �ȉ����J��Ԃ��A�Ō�̃f�[�^�ɂȂ�܂ōs���B
//
// ���Ԃ͎��̃f�[�^�Ɉڍs����܂ł̎��Ԃ��i�[����B
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
// �w�b�_���Q��
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
  // �S�Ẵf�[�^�̒ʒm���I����Ă���ꍇ��true���A��ł��c���Ă���ꍇ��false��Ԃ�
  bool Update(float elapsed_time);

  // Reset
  // �ŏ������蒼��
  void Reset(void);

  // Jump
  // �w�肳�ꂽ�Ԗڂ̃f�[�^�܂Ŗ��������
  // ���̍ۂɁA��΂��ꂽ�f�[�^�̒ʒm���X�g�͖��������
  void Jump(unsigned int data);

  // get
  unsigned int GetCurrentDataIndex(void) const { return current_index_; }

private:
  // _function
  void _Notify(void);

  // property
  DataContainerType data_;
  unsigned int current_index_;
  float sum_time_;  // �f�[�^�̒ʒm���s����x�Ƀ��Z�b�g�����
};
