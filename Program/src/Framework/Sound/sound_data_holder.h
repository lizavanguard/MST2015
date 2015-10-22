//==============================================================================
//
// SoundDataHolder
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <xaudio2.h>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SoundDataHolder {
public:
  SoundDataHolder(IXAudio2* p_xaudio, const char* p_filename, bool is_loop);
  ~SoundDataHolder();

  void Play(void);

  void Stop(void);

private:
  IXAudio2SourceVoice* p_source_voice_;
  BYTE* p_sound_data_;
  DWORD size_;
  bool is_loop_;
};
