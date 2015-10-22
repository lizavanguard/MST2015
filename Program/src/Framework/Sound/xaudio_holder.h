//==============================================================================
//
// XAduioHolder
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
class XAudioHolder {
public:
  XAudioHolder();
  ~XAudioHolder();

  IXAudio2* GetXAudio(void) { return p_xaudio_; }

private:
  static const int kObjectGenerateLimit = 1;

  static unsigned int s_num_object_;

  IXAudio2* p_xaudio_;
  IXAudio2MasteringVoice* p_mastering_voice_;
};
