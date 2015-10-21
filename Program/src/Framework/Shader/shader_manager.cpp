//==============================================================================
//
// _ShaderManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "shader_manager.h"

#include "Framework/Utility/DeviceHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
_ShaderManager::_ShaderManager() {
  std::string sFilePass = "./hlsl/";
  sFilePass += "/*.*";

  HANDLE hFind;
  WIN32_FIND_DATA fd;

  MY_BREAK_ASSERTMSG(INVALID_HANDLE_VALUE != (hFind = FindFirstFile(sFilePass.c_str(), &fd)), "ディレクトリが開きませんでした");
  if (INVALID_HANDLE_VALUE == hFind) {
    return;
  }

  // 変なファイル削除用
  FindNextFile(hFind, &fd);

  // ディレクトリを全て回す
  while (FindNextFile(hFind, &fd)) {
    LPD3DXEFFECT p_shader = nullptr;
    sFilePass = "./hlsl/";
    sFilePass += '/';
    sFilePass += fd.cFileName;
    // Thumbs.dbを飛ばす
    if (std::string(fd.cFileName) == "Thumbs.db") {
      continue;
    }

    liza::game::directx::LoadShader(DeviceHolder::Instance().GetDevice(), sFilePass.c_str(), &p_shader);

    //アサートチェック
    MY_BREAK_NULL_ASSERT(p_shader);

    //リリース時はなかった時点で失敗を返す
    if (!p_shader) {
      return;
    }

    // 拡張子を消す
    std::string texname = fd.cFileName;
    for (int i = texname.size(); i>0; --i)
    {
      if (texname[i - 1] == '.')
      {
        texname.pop_back();
        break;
      }
      texname.pop_back();
    }

    // BOXつめる
    //box->_pTex = p_shader;
    //box->_sGropName = pGropName;
    //box->_sTexName = texname;

    // 登録
    //container_.insert(std::pair<std::string, TEX_BOX*>(texname, box));
    container_.insert(std::make_pair(texname, p_shader));
  }

  // 検索終了
  FindClose(hFind);
}

//------------------------------------------------
// dtor
//------------------------------------------------
_ShaderManager::~_ShaderManager() {
  //ループでリスト全て回る
  for (auto it = container_.begin(); it != container_.end();)
  {
    //以下はタグに該当するテクスチャのみを処理している
    //ロード中テクスチャ情報のみを解放する
    SafeRelease(it->second);
    it = container_.erase(it);
  }
}

//------------------------------------------------
// get
//------------------------------------------------
LPD3DXEFFECT _ShaderManager::FindShader(const KeyType& shader_name) {
  auto it = container_.find(shader_name);
  MY_BREAK_ASSERTMSG(it != container_.end(), "シェーダがありませんでした");
  if (it == container_.end())
    return nullptr;

  //テクスチャを返却 NULLの場合そのまま返却
  return it->second;
}
