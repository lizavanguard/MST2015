//==============================================================================
//
// ステートクラス テンプレート [State.hpp]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __HPP_LIZAGAMESTATE_HPP__
#define __HPP_LIZAGAMESTATE_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace game {

template<typename T>
class State {
public:
	// dtor
	virtual ~State() {}

	// Entry
	virtual void Entry( T* pObject ) = 0;

	// Execute
	virtual void Execute( T* pObject ) = 0;

	// Exit
	virtual void Exit( T* pObject ) = 0;
};

	} // namespace game
} // namespace liza


#endif // __HPP_LIZAGAMESTATE_HPP__