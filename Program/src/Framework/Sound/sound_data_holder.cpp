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

  // バッファのクリア
  memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

  // サウンドデータファイルの生成
  hFile = CreateFile(p_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
  MY_BREAK_ASSERTMSG(hFile != INVALID_HANDLE_VALUE, "サウンドデータファイルの生成に失敗！(1)");
  if (hFile == INVALID_HANDLE_VALUE) {
    return;
  }

  // ファイルポインタを先頭に移動
  DWORD ret = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
  MY_BREAK_ASSERTMSG(ret != INVALID_SET_FILE_POINTER, "サウンドデータファイルの生成に失敗！(2)");
  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
    return;
  }

  // WAVEファイルのチェック
  HRESULT hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("WAVEファイルのチェックに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
  _HR_ASSERT("WAVEファイルのチェックに失敗！(2)");
  if (FAILED(hr)) {
    return;
  }
  _HR_ASSERT("WAVEファイルのチェックに失敗！(3)");
  if (dwFiletype != 'EVAW') {
    return;
  }

  // フォーマットチェック
  hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
  _HR_ASSERT("フォーマットチェックに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
  _HR_ASSERT("フォーマットチェックに失敗！(2)");
  if (FAILED(hr)) {
    return;
  }

  // オーディオデータ読み込み
  hr = CheckChunk(hFile, 'atad', &size_, &dwChunkPosition);
  _HR_ASSERT("オーディオデータ読み込みに失敗！(1)");
  if (FAILED(hr)) {
    return;
  }
  p_sound_data_ = (BYTE*)malloc(size_);
  hr = ReadChunkData(hFile, p_sound_data_, size_, dwChunkPosition);
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
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition) {
  HRESULT hr = S_OK;
  DWORD dwRead;
  DWORD dwChunkType;
  DWORD dwChunkDataSize;
  DWORD dwRIFFDataSize = 0;
  DWORD dwFileType;
  DWORD dwBytesRead = 0;
  DWORD dwOffset = 0;

  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// ファイルポインタを先頭に移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK) {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0) {// チャンクの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0) {// チャンクデータの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType) {
      case 'FFIR':
        dwRIFFDataSize = dwChunkDataSize;
        dwChunkDataSize = 4;
        if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0) {// ファイルタイプの読み込み
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER) {// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//------------------------------------------------
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset) {
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {// ファイルポインタを指定位置まで移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0) {// データの読み込み
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

