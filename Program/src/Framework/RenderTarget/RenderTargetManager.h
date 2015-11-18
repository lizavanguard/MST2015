//==============================================================================
//
// RenderTargetManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "RenderTargetConfig.h"

#include "liza/generic/SingletonHolder.hpp"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace liza {
  namespace game {
    namespace directx {
      class RenderTargetHolder;
    }
  }
}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class _RenderTargetManager {
  using DataType = liza::game::directx::RenderTargetHolder*;
  using ContainerType = std::vector<DataType>;

public:
  // ctor
  _RenderTargetManager(unsigned int num_render_targets);

  // dtor
  ~_RenderTargetManager();

  // Assign render target
  void Assign(void);

  // UnAssign
  void UnAssign(void);

  // Clear
  void Clear(void);

  // Get texture
  LPDIRECT3DTEXTURE9 GetTexture(unsigned int index) const;

private:
  bool _CheckIndex(unsigned int index) const;

  // property
  unsigned int num_render_targets_;
  ContainerType container_;
};

// HACK:
template<typename T>
struct CreateRenderTargetManager {
  static T* Create(void) {
    return new T(kNumRenderTargets);
  }

  static void Destroy(T* p_instance) {
    assert(p_instance != nullptr);
    delete p_instance;
  }
};

// alias
using RenderTargetManager = liza::generic::SingletonHolder<_RenderTargetManager, CreateRenderTargetManager>;
