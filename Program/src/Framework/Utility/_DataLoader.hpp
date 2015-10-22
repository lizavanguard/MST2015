//==============================================================================
//
// _DataLoader
// Author: Shimizu Shoji
//
// DataLoaderにて使用するDestroyPolicyを満足するクラス群
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
