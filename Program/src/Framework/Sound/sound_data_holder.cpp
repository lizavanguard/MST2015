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
  HANDLE h_file;
  DWORD dwChunkSize = 0;
  DWORD dwChunkPosition = 0;
  DWORD dwFiletype;
  WAVEFORMATEXTENSIBLE wfx;
  XAUDIO2_BUFFER buffer;

  // �o�b�t�@�̃N���A
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // �T�E���h�f�[�^�t�@�C���̐���
  h_file = CreateFile(p_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  MY_BREAK_ASSERTMSG(h_file != INVALID_HANDLE_VALUE, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)");
  if (h_file == INVALID_HANDLE_VALUE) {
    return;
  }

  // �t�@�C���|�C���^��擪�Ɉړ�
  DWORD ret = SetFilePointer(h_file, 0, NULL, FILE_BEGIN);
  MY_BREAK_ASSERTMSG(ret != INVALID_SET_FILE_POINTER, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)");
  if (SetFilePointer(h_file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
    return;
  }

  // WAVE�t�@�C���̃`�F�b�N
  HRESULT hr = _CheckChunk(h_file, 'FFIR', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = _ReadChunkData(h_file, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)");
  if (FAILED(hr)) {
    return;
  }
  _HR_ASSERT("WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)");
  if (dwFiletype != 'EVAW') {
    return;
  }

  // �t�H�[�}�b�g�`�F�b�N
  hr = _CheckChunk(h_file, ' tmf', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = _ReadChunkData(h_file, &wfx, dwChunkSize, dwChunkPosition);
  _HR_ASSERT("�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)");
  if (FAILED(hr)) {
    return;
  }

  // �I�[�f�B�I�f�[�^�ǂݍ���
  hr = _CheckChunk(h_file, 'atad', &size_, &dwChunkPosition);
  _HR_ASSERT("�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)");
  if (FAILED(hr)) {
    return;
  }
  p_sound_data_ = (BYTE*)malloc(size_);
  hr = _ReadChunkData(h_file, p_sound_data_, size_, dwChunkPosition);
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
HRESULT SoundDataHolder::_CheckChunk(HANDLE h_file, DWORD format, DWORD *p_chunk_size, DWORD *p_chunk_data_position) {
  HRESULT hr = S_OK;
  DWORD read;
  DWORD chunk_type;
  DWORD chunk_data_size;
  DWORD riff_data_size = 0;
  DWORD file_type;
  DWORD bytes_read = 0;
  DWORD offset = 0;

  if (SetFilePointer(h_file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^��擪�Ɉړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK) {
    if (ReadFile(h_file, &chunk_type, sizeof(DWORD), &read, NULL) == 0) {// �`�����N�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(h_file, &chunk_data_size, sizeof(DWORD), &read, NULL) == 0) {// �`�����N�f�[�^�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (chunk_type) {
      case 'FFIR':
        riff_data_size = chunk_data_size;
        chunk_data_size = 4;
        if (ReadFile(h_file, &file_type, sizeof(DWORD), &read, NULL) == 0) {// �t�@�C���^�C�v�̓ǂݍ���
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(h_file, chunk_data_size, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
          return HRESULT_FROM_WIN32(GetLastError());
        }
    }

    offset += sizeof(DWORD)* 2;
    if (chunk_type == format) {
      *p_chunk_size = chunk_data_size;
      *p_chunk_data_position = offset;

      return S_OK;
    }

    offset += chunk_data_size;
    if (bytes_read >= riff_data_size) {
      return S_FALSE;
    }
  }

  return S_OK;
}

//------------------------------------------------
// �`�����N�f�[�^�̓ǂݍ���
//------------------------------------------------
HRESULT SoundDataHolder::_ReadChunkData(HANDLE h_file, void *p_buffer, DWORD buffer_size, DWORD buffer_offset) {
  DWORD read;

  if (SetFilePointer(h_file, buffer_offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// �t�@�C���|�C���^���w��ʒu�܂ňړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(h_file, p_buffer, buffer_size, &read, NULL) == 0) {// �f�[�^�̓ǂݍ���
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

