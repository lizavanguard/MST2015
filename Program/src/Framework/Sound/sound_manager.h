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

#include "Framework/Utility/GroupDataFinder.hpp"

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
  using ContainerType = GroupDataFinder<DataType, UsingDelete>;

public:
  // ctor
  _SoundManager();

  // dtor
  ~_SoundManager();

  // Load
  void Load(void);

  // Play sound
  bool PlaySound(const ContainerType::KeyType& sound_file_name);

  // Stop sound
  void StopSound(const ContainerType::KeyType& sound_file_name);
  // Stop sound all
  void StopSound(void);

private:
  ContainerType* p_container_;
  XAudioHolder* p_xaudio_;
};

using SoundManager = liza::generic::SingletonHolder<_SoundManager>;
