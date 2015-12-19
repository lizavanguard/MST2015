//==============================================================================
//
// GameConfig
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {
  static const unsigned int kScorePlaceMax = 3;
  static const unsigned int kThrowingMax = 2;
  static const D3DXVECTOR3 kScoreBoardPosition(400, 100, 0);
  static const D3DXVECTOR2 kScoreBoardSize(991 * 0.5f, 150 * 0.5f);
  static const D3DXVECTOR2 kScorePositions[kThrowingMax] = {
    D3DXVECTOR2(kScoreBoardPosition.x - 75.0f, kScoreBoardPosition.y),
    D3DXVECTOR2(kScoreBoardPosition.x + 200.0f, kScoreBoardPosition.y)
  };
  static const D3DXVECTOR2 kScoreSize(50.0f, 50.0f);

  static const float kGarterDistance = 2000;
}
