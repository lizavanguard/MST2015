//==============================================================================
//
// SoundDataHolder
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "sound_data_holder.h"

//------------------------------------------------
//------------------------------------------------
static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);

//------------------------------------------------
//------------------------------------------------
static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SoundDataHolder::SoundDataHolder(IXAudio2* p_xaudio, const char* p_filename, const bool is_loop)
    : p_source_voice_(nullptr)
    , p_sound_data_(nullptr)
    , size_(0)
    , is_loop_(is_loop) {
#define _HR_ASSERT(x) MY_BREAK_ASSERTMSG(SUCCEEDED(hr), x);
  HANDLE hFile;
  DWORD dwChunkSize = 0;
  DWORD dwChunkPosition = 0;
  DWORD dwFiletype;
  WAVEFORMATEXTENSIBLE wfx;
  XAUDIO2_BUFFER buffer;

  // �o�b�t�@�̃N���A
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // �T�E���h�f�[�^�t�@�C���̐���
  hFile = CreateFile(p_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  MY_BREAK_ASSERTMSG(hFile != INVALID_HANDLE_VALUE, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)");
  if (hFile == INVALID_HANDLE_VALUE) {
    return;
  }

  // �t�@�C���|�C���^��擪�Ɉړ�
  DWORD ret = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  MY_BREAK_ASSERTMSG(ret != INVALID_SET_FILE_POINTER, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)");
  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
    return;
  }

  // WAVE�t�@�C���̃`�F�b�N
  HRESULT hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
  if (FAILED(hr)) {
    return;
  }
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
  if (dwFiletype != 'EVAW') {
    return;
  }

  // �t�H�[�}�b�g�`�F�b�N
  hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
  _HR_ASSERT("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");
  if (FAILED(hr)) {
    return;
  }

  // �I�[�f�B�I�f�[�^�ǂݍ���
  hr = CheckChunk(hFile, 'atad', &size_, &dwChunkPosition);
  _HR_ASSERT("�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  p_sound_data_ = (BYTE*)malloc(size_);
  hr = ReadChunkData(hFile, p_sound_data_, size_, dwChunkPosition);
  _HR_ASSERT("�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)");
  if (FAILED(hr)) {
    return;
  }

  // �\�[�X�{�C�X�̐���
  hr = p_xaudio->CreateSourceVoice(&p_source_voice_, &(wfx.Format));
  _HR_ASSERT("�\�[�X�{�C�X�̐����Ɏ��s�I");
  if (FAILED(hr)) {
    return;
  }

  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = size_;
  buffer.pAudioData = p_sound_data_;
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = 0;

  // �I�[�f�B�I�o�b�t�@�̓o�^
  p_source_voice_->SubmitSourceBuffer(&buffer);
#undef _HR_ASSERT
}

//------------------------------------------------
// dtor
//------------------------------------------------
SoundDataHolder::~SoundDataHolder() {
  if (p_source_voice_) {
    p_source_voice_->Stop(0);
    p_source_voice_->DestroyVoice();
    p_source_voice_ = nullptr;
  }

  if (p_sound_data_) {
    free(p_sound_data_);
    p_sound_data_ = nullptr;
  }
}

//------------------------------------------------
// Play
//------------------------------------------------
void SoundDataHolder::Play(void) {
  XAUDIO2_VOICE_STATE xa2state;
  XAUDIO2_BUFFER buffer;

  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = size_;
  buffer.pAudioData = p_sound_data_;
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = is_loop_ ? 0xffffffff : 0;

  // ��Ԏ擾
  p_source_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0) {// �Đ���
    // �ꎞ��~
    p_source_voice_->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    p_source_voice_->FlushSourceBuffers();
  }

  // �I�[�f�B�I�o�b�t�@�̓o�^
  p_source_voice_->SubmitSourceBuffer(&buffer);

  // �Đ�
  p_source_voice_->Start(0);
}

//------------------------------------------------
// Stop
//------------------------------------------------
void SoundDataHolder::Stop(void) {
  XAUDIO2_VOICE_STATE xa2state;

  // ��Ԏ擾
  p_source_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0) {// �Đ���
    // �ꎞ��~
    p_source_voice_->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    p_source_voice_->FlushSourceBuffers();
  }

}

//------------------------------------------------
// �`�����N�̃`�F�b�N
//------------------------------------------------
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition) {
  HRESULT hr = S_OK;
  DWORD dwRead;
  DWORD dwChunkType;
  DWORD dwChunkDataSize;
  DWORD dwRIFFDataSize = 0;
  DWORD dwFileType;
  DWORD dwBytesRead = 0;
  DWORD dwOffset = 0;

  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^��擪�Ɉړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK) {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0) {// �`�����N�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0) {// �`�����N�f�[�^�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType) {
      case 'FFIR':
        dwRIFFDataSize = dwChunkDataSize;
        dwChunkDataSize = 4;
        if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0) {// �t�@�C���^�C�v�̓ǂݍ���
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
          return HRESULT_FROM_WIN32(GetLastError());
        }
    }

    dwOffset += sizeof(DWORD)* 2;
    if (dwChunkType == format) {
      *pChunkSize = dwChunkDataSize;
      *pChunkDataPosition = dwOffset;

      return S_OK;
    }

    dwOffset += dwChunkDataSize;
    if (dwBytesRead >= dwRIFFDataSize) {
      return S_FALSE;
    }
  }

  return S_OK;
}

//------------------------------------------------
// �`�����N�f�[�^�̓ǂݍ���
//------------------------------------------------
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset) {
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^���w��ʒu�܂ňړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0) {// �f�[�^�̓ǂݍ���
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

