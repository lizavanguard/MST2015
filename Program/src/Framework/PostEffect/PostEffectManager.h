//==============================================================================
//
// PostEffectManager
// Author: Shimizu Shoji
//
// �|�X�g�G�t�F�N�g�Ǘ��N���X
// �ŏI�I�Ƀt���[���o�b�t�@�ɕ`�悷�邽�߂̃e�N�X�`�����ꖇ����
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "liza/game/directx/render_target_holder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// namespace
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace post_effect {
  class PostEffect;
}

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace post_effect {

class PostEffectManager {
  // alias
  using ContainerType = std::list<PostEffect*>;

public:
  // ctor
  PostEffectManager();

  // dtor
  ~PostEffectManager();

  // Process
  void Process();

private:
  LPD3DXEFFECT p_shader_;
  ContainerType post_effects_;
};

}  // namespace post_effect
