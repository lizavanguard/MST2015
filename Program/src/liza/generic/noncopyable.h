//==============================================================================
//
// �R�s�[/����֎~�C���^�t�F�[�X
// Author : Shimizu Shoji
//
// �R�s�[�Ƒ�����֎~���邽�߂̃C���^�t�F�[�X�ł��B
// ���̃N���X��public�p�����Ă��������B
// static_assert �Ƃ����ꂽ�ق����e�؂���
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

// �ڂ����̓t�@�C���w�b�_�ɂĐ����B
template<class T>
class NonCopyable {
protected:
  NonCopyable() {}
  ~NonCopyable() {}

private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable &);
  //T& operator=(const T &);  // ���ꂾ�ƃR�s�[�ł��Ă��܂�
};

}  // namespace generic
}  // namespace liza

#endif  // __H_LIZA_GENERIC_NONCOPYABLE_H__
