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
  HRESULT _CheckChunk(HANDLE h_file, DWORD format, DWORD* p_chunk_size, DWORD* p_chunk_data_position);
  HRESULT _ReadChunkData(HANDLE h_file, void* p_buffer, DWORD buffer_size, DWORD buffer_offset);

  IXAudio2SourceVoice* p_source_voice_;
  BYTE* p_sound_data_;
  DWORD size_;
  bool is_loop_;
};
