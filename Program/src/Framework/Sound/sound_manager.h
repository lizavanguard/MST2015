//==============================================================================
//
// SoundManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <xaudio2.h>

#include "liza/generic/SingletonHolder.hpp"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙型定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// サウンドファイル一覧
//------------------------------------------------
typedef enum {
  SOUND_LABEL_BGM1,
  SOUND_LABEL_SE1,
  kSoundMax
} SoundLabels;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _SoundManager {
public:
  // ctor
  _SoundManager();

  // dtor
  ~_SoundManager();

  // Load
  void Load(void);

  // Play sound
  bool PlaySound(SoundLabels label);

  // Stop sound
  void StopSound(SoundLabels label);
  void StopSound(void);

};

using SoundManager = liza::generic::SingletonHolder<_SoundManager>;
