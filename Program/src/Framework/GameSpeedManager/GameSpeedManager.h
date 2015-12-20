//==============================================================================
//
// GameSpeedManager
// Author: Shimizu Shoji
//
// �Q�[���̐i�s���x���Ǘ�����N���X
// ���x����ύX����Ƒ����Ȃ�����x���Ȃ�����
// �������A�e�����󂯂�̂͂�������ƌo�ߎ��Ԃ𗘗p���Ă���N���X�̂�
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/generic/ServiceLocator.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameSpeedManager {
public:
  // ctor
  GameSpeedManager();

  // dtor
  ~GameSpeedManager();

  // Update
  // return = elapsed_time * game_speed_rate
  float Update(float elapsed_time);

  // get
  float GetSpeedRate(void) const { return speed_rate_; }

  // set
  void SetSpeedRate(float speed_rate) { speed_rate_ = speed_rate; _CheckSpeed(); }

  // add
  void AddSpeedRate(float speed_rate) { speed_rate_ += speed_rate; _CheckSpeed(); }

private:
  // _function
  void _CheckSpeed(void);
  void _DebugControlSpeed(void);

  // property
  float speed_rate_;
  float latest_elapsed_time_;
  float latest_raw_elapsed_time_;
};

using GameSpeedManagerServiceLocator = liza::generic::ServiceLocator<GameSpeedManager>;
