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

  MY_BREAK_ASSERTMSG(INVALID_HANDLE_VALUE != (hFind = FindFirstFile(sFilePass.c_str(), &fd)), "�f�B���N�g�����J���܂���ł���");
  if (INVALID_HANDLE_VALUE == hFind) {
    return;
  }

  // �ςȃt�@�C���폜�p
  FindNextFile(hFind, &fd);

  // �f�B���N�g����S�ĉ�
  while (FindNextFile(hFind, &fd)) {
    LPD3DXEFFECT p_shader = nullptr;
    sFilePass = "./hlsl/";
    sFilePass += '/';
    sFilePass += fd.cFileName;
    // Thumbs.db���΂�
    if (std::string(fd.cFileName) == "Thumbs.db") {
      continue;
    }

    liza::game::directx::LoadShader(DeviceHolder::Instance().GetDevice(), sFilePass.c_str(), &p_shader);

    //�A�T�[�g�`�F�b�N
    MY_BREAK_NULL_ASSERT(p_shader);

    //�����[�X���͂Ȃ��������_�Ŏ��s��Ԃ�
    if (!p_shader) {
      return;
    }

    // �g���q������
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

    // BOX�߂�
    //box->_pTex = p_shader;
    //box->_sGropName = pGropName;
    //box->_sTexName = texname;

    // �o�^
    //container_.insert(std::pair<std::string, TEX_BOX*>(texname, box));
    container_.insert(std::make_pair(texname, p_shader));
  }

  // �����I��
  FindClose(hFind);
}

//------------------------------------------------
// dtor
//------------------------------------------------
_ShaderManager::~_ShaderManager() {
  //���[�v�Ń��X�g�S�ĉ��
  for (auto it = container_.begin(); it != container_.end();)
  {
    //�ȉ��̓^�O�ɊY������e�N�X�`���݂̂��������Ă���
    //���[�h���e�N�X�`�����݂̂��������
    SafeRelease(it->second);
    it = container_.erase(it);
  }
}

//------------------------------------------------
// get
//------------------------------------------------
LPD3DXEFFECT _ShaderManager::FindShader(const KeyType& shader_name) {
  auto it = container_.find(shader_name);
  MY_BREAK_ASSERTMSG(it != container_.end(), "�V�F�[�_������܂���ł���");
  if (it == container_.end())
    return nullptr;

  //�e�N�X�`����ԋp NULL�̏ꍇ���̂܂ܕԋp
  return it->second;
}
