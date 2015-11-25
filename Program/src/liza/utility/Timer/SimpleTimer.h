//==============================================================================
//
// SimpleTimer
// Author: Shimizu Shoji
//
// ��{�I�ȃ^�C�}�[
// 1 => 1s, 0.001 => 1ms
// �X�^�[�g������̌o�ߎ��Ԃ��J�E���g����
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
namespace utility {

// �ڍׂ̓t�@�C���w�b�_���Q��
class SimpleTimer {
public:
  // ctor
  // �^�C�}�[�̒ʒm�Ԋu��ݒ肷��
  SimpleTimer();

  // �o�ߎ��Ԃ��X�V���A�Ԃ�
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
