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

#include "Framework/Utility/DataFinder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SoundDataHolder;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �񋓌^��`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// �T�E���h�t�@�C���ꗗ
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
  using DataType = SoundDataHolder*;
  using ContainerType = DataFinder<DataType, UsingDelete>;

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
  void StopSound(void);

private:
  ContainerType* p_container_;
};

using SoundManager = liza::generic::SingletonHolder<_SoundManager>;
