//==============================================================================
//
// HudTimer [HudTimer.h]
// Created : Shimizu Shoji
//
//==============================================================================
#ifndef __H_HUDTIMER_H__
#define __H_HUDTIMER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HudNumber;

namespace liza {
  namespace utility {
    class Timer;
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class HudTimer {
public:
  // ctor
  HudTimer(
    unsigned int placeMax,	// ®”Œ…
    unsigned int decimalPlaceMax,	// ¬”“_Œ…
    const Vector2& pos,
    const Vector2& size,
    bool isCountUp = true
    );

  // dtor
  ~HudTimer();

  // Update
  void Update(float elapsedTime);

  // Draw
  void Draw(void);

  // Assign Time
  void AssignTime(float time);

  // get
  float GetTime(void) const;
  bool IsEventHappened(void) const { return isEventHappened_; }

private:
  // Update Numbers
  void _UpdateNumbers(void);

  // property
  HudNumber* pHudNumber_;
  HudNumber* pHudDecimalNumber_;
  liza::utility::Timer* pTimer_;
  unsigned int decimalPlaceMax_;	// ¬”“_Œ…”
  unsigned int placeMax_;	// ®”Œ…”
  bool isEventHappened_;
  bool isDecimalNumberActive_;
  bool isNumberActive_;
};

#endif // __H_HUDTIMER_H__