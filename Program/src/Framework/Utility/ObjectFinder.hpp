//==============================================================================
//
// ObjectFinder
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <map>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
class ObjectFinder {
private:
  using KeyType = std::string;
  using DataType = T;
  using ContainerType = std::map<KeyType, DataType>;
  using LoadFunctionType = void (*)(T* p_data);

public:
  // ctor
  ObjectFinder(const char* p_start_directory_path, LoadFunctionType function);

  // dtor
  ~ObjectFinder();

  // find data
  T Find(const KeyType& key);

private
  // property
  ContainerType container_;
};

template<typename T>
ObjectFinder<T>::ObjectFinder(const char* p_start_directory_path, LoadFunctionType function) {
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

    // �o�^
    container_.insert(std::make_pair(texname, p_shader));
  }

  // �����I��
  FindClose(hFind);
}