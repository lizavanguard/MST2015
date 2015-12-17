//==============================================================================
//
// ScoreHolder
// Author: Shimizu Shoji
//
// 最新のスコアと最高のスコアを保存する
// 最新のスコアと最高のスコアが同じであったら通知される
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <math.h>

#include <liza/generic/ServiceLocator.hpp>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class ScoreHolder {
public:
  // ctor
  ScoreHolder() : high_score_(0), latest_score_(0) {}

  // dtor
  ~ScoreHolder() {}

  // set
  void AssignLatestScore(unsigned int latest_score) {
    latest_score_ = latest_score;
    high_score_ = std::max<unsigned int>(latest_score_, high_score_);
  }

  // get
  unsigned int GetLatestScore(void) const { return latest_score_; }
  unsigned int GetHighScore(void) const { return high_score_; }
  bool IsHighScore(void) const { return latest_score_ == high_score_; }

  // set
  void SetLatestScore(unsigned int latest_score) { latest_score_ = latest_score; }
  void SetHighScore(unsigned int high_score) { high_score_ = high_score; }

private:
  unsigned int high_score_;
  unsigned int latest_score_;
};

using ScoreHolderServiceLocator = liza::generic::ServiceLocator<ScoreHolder>;
