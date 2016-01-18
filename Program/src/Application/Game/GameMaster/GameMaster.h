//==============================================================================
//
// GameMaster
// Author: Shimizu Shoji
//
// STATE:
//  READY
//  PLAYER_INPUT
//  WATCH
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class CollisionManager;
class HudNumber;
class PinManager;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameMaster {
  static const int kThrowCountMax = 2;

public:
  // ctor
  GameMaster(HudNumber** pp_hud_pin_number, PinManager& pin_manager, CollisionManager& collision_master);

  // dtor
  ~GameMaster();

  // update
  void Update(float elapsed_time);

  // add threw count
  void GoToNextThrowing(void) { ++threw_count_; }

  // 
  void CalculateScore(void);

  // end game
  void EndGame(void) { is_end_game_ = true; }
  void OnReplayMode(void) { is_replay_mode_ = true; }
  void OffReplayMode(void) { is_replay_mode_ = false; }

  // get
  unsigned int GetThrowCount(void) const { return threw_count_; }
  unsigned int GetScore(unsigned int throw_count) const { return scores_[throw_count]; }
  unsigned int GetScoreSum(void) const { return std::accumulate(scores_.begin(), scores_.end(), 0); }
  float GetShootTime(void) const { return shoot_time_; }
  bool IsLastThrow(void) const { return threw_count_ == kThrowCountMax - 1; }
  bool IsEndGame(void) const { return is_end_game_; }

  // set
  void SetShootTime(float shoot_time) { shoot_time_ = shoot_time; }

private:
  bool _IsFallen(const D3DXVECTOR3& rotation) const;

  unsigned int threw_count_;
  bool is_end_game_;
  bool is_replay_mode_;
  float shoot_time_;
  std::array<unsigned int, kThrowCountMax> scores_;

  HudNumber** pp_hud_pin_number_;
  CollisionManager& collision_manager_;
  PinManager& pin_manager_;
};
