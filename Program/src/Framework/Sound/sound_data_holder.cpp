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

  // バッファのクリア
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // サウンドデータファイルの生成
  h_file = CreateFile(p_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  MY_BREAK_ASSERTMSG(h_file != INVALID_HANDLE_VALUE, "サウンドデータファイルの生成に失敗！(1)");
  if (h_file == INVALID_HANDLE_VALUE) {
    return;
  }

  // ファイルポインタを先頭に移動
  DWORD ret = SetFilePointer(h_file, 0, NULL, FILE_BEGIN);
  MY_BREAK_ASSERTMSG(ret != INVALID_SET_FILE_POINTER, "サウンドデータファイルの生成に失敗！(2)");
  if (SetFilePointer(h_file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
    return;
  }

  // WAVEファイルのチェック
  HRESULT hr = _CheckChunk(h_file, 'FFIR', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("WAVEファイルのチェックに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = _ReadChunkData(h_file, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  _HR_ASSERT("WAVEファイルのチェックに失敗！(2)");
  if (FAILED(hr)) {
    return;
  }
  _HR_ASSERT("WAVEファイルのチェックに失敗！(3)");
  if (dwFiletype != 'EVAW') {
    return;
  }

  // フォーマットチェック
  hr = _CheckChunk(h_file, ' tmf', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("フォーマットチェックに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = _ReadChunkData(h_file, &wfx, dwChunkSize, dwChunkPosition);
  _HR_ASSERT("フォーマットチェックに失敗！(2)");
  if (FAILED(hr)) {
    return;
  }

  // オーディオデータ読み込み
  hr = _CheckChunk(h_file, 'atad', &size_, &dwChunkPosition);
  _HR_ASSERT("オーディオデータ読み込みに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  p_sound_data_ = (BYTE*)malloc(size_);
  hr = _ReadChunkData(h_file, p_sound_data_, size_, dwChunkPosition);
  _HR_ASSERT("オーディオデータ読み込みに失敗！(2)");
  if (FAILED(hr)) {
    return;
  }

  // ソースボイスの生成
  hr = p_xaudio->CreateSourceVoice(&p_source_voice_, &(wfx.Format));
  _HR_ASSERT("ソースボイスの生成に失敗！");
  if (FAILED(hr)) {
    return;
  }

  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = size_;
  buffer.pAudioData = p_sound_data_;
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = 0;

  // オーディオバッファの登録
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

  // 状態取得
  p_source_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0) {// 再生中
    // 一時停止
    p_source_voice_->Stop(0);

    // オーディオバッファの削除
    p_source_voice_->FlushSourceBuffers();
  }

  // オーディオバッファの登録
  p_source_voice_->SubmitSourceBuffer(&buffer);

  // 再生
  p_source_voice_->Start(0);
}

//------------------------------------------------
// Stop
//------------------------------------------------
void SoundDataHolder::Stop(void) {
  XAUDIO2_VOICE_STATE xa2state;

  // 状態取得
  p_source_voice_->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0) {// 再生中
    // 一時停止
    p_source_voice_->Stop(0);

    // オーディオバッファの削除
    p_source_voice_->FlushSourceBuffers();
  }

}

//------------------------------------------------
// チャンクのチェック
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

  if (SetFilePointer(h_file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// ファイルポインタを先頭に移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK) {
    if (ReadFile(h_file, &chunk_type, sizeof(DWORD), &read, NULL) == 0) {// チャンクの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(h_file, &chunk_data_size, sizeof(DWORD), &read, NULL) == 0) {// チャンクデータの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (chunk_type) {
      case 'FFIR':
        riff_data_size = chunk_data_size;
        chunk_data_size = 4;
        if (ReadFile(h_file, &file_type, sizeof(DWORD), &read, NULL) == 0) {// ファイルタイプの読み込み
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(h_file, chunk_data_size, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) {// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//------------------------------------------------
HRESULT SoundDataHolder::_ReadChunkData(HANDLE h_file, void *p_buffer, DWORD buffer_size, DWORD buffer_offset) {
  DWORD read;

  if (SetFilePointer(h_file, buffer_offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// ファイルポインタを指定位置まで移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(h_file, p_buffer, buffer_size, &read, NULL) == 0) {// データの読み込み
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

