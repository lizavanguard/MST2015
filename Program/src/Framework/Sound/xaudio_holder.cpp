//==============================================================================
//
// XAduioHolder
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "xaudio_holder.h"

//==============================================================================
// class implementation
//==============================================================================
unsigned int XAudioHolder::s_num_object_ = 0;

XAudioHolder::XAudioHolder()
    : p_xaudio_(nullptr)
    , p_mastering_voice_(nullptr) {
#define _HR_ASSERT(x) MY_BREAK_ASSERTMSG(SUCCEEDED(hr), x);
  if (s_num_object_ == 0) {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  }
  MY_BREAK_ASSERTMSG(s_num_object_ < kObjectGenerateLimit, "生成しすぎ");
  if (s_num_object_ == kObjectGenerateLimit) {
    return;
  }
  ++s_num_object_;

  HRESULT hr = XAudio2Create(&p_xaudio_, 0);
  _HR_ASSERT("XAudio2オブジェクトの作成に失敗！");
  if (FAILED(hr)) {
    CoUninitialize();
    return;
  }

  hr = p_xaudio_->CreateMasteringVoice(&p_mastering_voice_);
  _HR_ASSERT("マスターボイスの生成に失敗！");
  if (FAILED(hr)) {
    SafeRelease(p_xaudio_);
    CoUninitialize();
    return;
  }

#undef _HR_ASSERT
}

XAudioHolder::~XAudioHolder() {
  if (p_mastering_voice_) {
    p_mastering_voice_->DestroyVoice();
    p_mastering_voice_ = nullptr;
  }

  SafeRelease(p_xaudio_);

  --s_num_object_;
  if (s_num_object_ == 0) {
    CoUninitialize();
  }
}
