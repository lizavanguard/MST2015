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

#include "Framework/Utility/GroupDataLoader.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SoundDataHolder;
class XAudioHolder;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _SoundManager {
  using DataType = SoundDataHolder*;
  using ContainerType = GroupDataLoader<DataType, UsingDelete>;

public:
  // ctor
  _SoundManager();

  // dtor
  ~_SoundManager();

  // Load
  void Load(void);

  // Play sound
  bool PlayBGM(const ContainerType::KeyType& sound_file_name);
  bool PlaySE(const ContainerType::KeyType& sound_file_name);

  // Stop sound
  void StopSound(const ContainerType::KeyType& sound_file_name);
  // Stop sound all
  void StopSound(void);

  // get
  IXAudio2* GetXAudio2(void) const;

  // Set
  void Activate(void) { is_active_ = true; }
  void Deactivate(void) { is_active_ = false; }

private:
  // _function
  bool _PlaySound(const ContainerType::KeyType& sound_file_name);

  // property
  ContainerType* p_container_;
  XAudioHolder* p_xaudio_;
  bool is_active_;
};

using SoundManager = liza::generic::SingletonHolder<_SoundManager>;
