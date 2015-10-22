//==============================================================================
//
// _DataFinder
// Author: Shimizu Shoji
//
// DataFinder�ɂĎg�p����DestroyPolicy�𖞑�����N���X�Q
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/SafeRelease.h"
#include "liza/SafeDelete.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
template<typename T>
struct UsingRelease {
  static void Destroy(T data) {
    SafeRelease(data);
  }
};

template<typename T>
struct UsingDelete {
  static void Destroy(T data) {
    SafeDelete(data);
  }
};
