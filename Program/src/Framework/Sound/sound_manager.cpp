//==============================================================================
//
// SoundManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "sound_manager.h"

#include "sound_data_holder.h"
#include "xaudio_holder.h"

//==============================================================================
// class implementation
//==============================================================================

//------------------------------------------------
// ctor
//------------------------------------------------
_SoundManager::_SoundManager()
    : p_container_(nullptr)
    , p_xaudio_(nullptr)
    , is_active_(true) {
  XAudioHolder* p_xaudio = new XAudioHolder();
  p_container_ = new ContainerType("data/Sound/");
  p_container_->Load("Bgm", [p_xaudio](const char* p_filename, DataType* p_sound_data) {
    *p_sound_data = new SoundDataHolder(p_xaudio->GetXAudio(), p_filename, true);
  });
  p_container_->Load("Se", [p_xaudio](const char* p_filename, DataType* p_sound_data) {
    *p_sound_data = new SoundDataHolder(p_xaudio->GetXAudio(), p_filename, false);
  });

  p_xaudio_ = p_xaudio;
}

//------------------------------------------------
// dtor
//------------------------------------------------
_SoundManager::~_SoundManager() {
  SafeDelete(p_container_);
  SafeDelete(p_xaudio_);
}

//------------------------------------------------
// Play
//------------------------------------------------
bool _SoundManager::PlayBGM(const ContainerType::KeyType& sound_file_name) {
  if (!is_active_) {
    return false;
  }
  std::string filename = "BGM/";
  filename += sound_file_name;
  return _PlaySound(filename);
}

bool _SoundManager::PlaySE(const ContainerType::KeyType& sound_file_name) {
  if (!is_active_) {
    return false;
  }
  std::string filename = "SE/";
  filename += sound_file_name;
  return _PlaySound(filename);
}

//------------------------------------------------
// Stop sound
//------------------------------------------------
void _SoundManager::StopSound(const ContainerType::KeyType& sound_file_name) {
  DataType data = p_container_->Find(sound_file_name);
  MY_BREAK_ASSERTMSG(data != nullptr, "そんなファイルないよ");
  if (!data) {
    return;
  }

  data->Stop();
}

//------------------------------------------------
// Stop sound all
//------------------------------------------------
void _SoundManager::StopSound(void) {
  for (unsigned int i = 0; i < p_container_->size(); ++i) {
    auto inner_container = p_container_->GetContainer(i);
    for (auto it : *inner_container) {
      (it.second)->Stop();
    }
  }
  //p_container_
  //for (auto data : p_container_) {
  //  data.second->Stop();
  //}
}

//------------------------------------------------
// get
//------------------------------------------------
IXAudio2* _SoundManager::GetXAudio2(void) const {
  return p_xaudio_->GetXAudio();
}

//------------------------------------------------
// _Play sound
//------------------------------------------------
bool _SoundManager::_PlaySound(const ContainerType::KeyType& sound_file_name) {
  DataType data = p_container_->Find(sound_file_name);
  MY_BREAK_ASSERTMSG(data != nullptr, "そんなファイルないよ");
  if (!data) {
    return false;
  }

  data->Play();
  return true;
}
