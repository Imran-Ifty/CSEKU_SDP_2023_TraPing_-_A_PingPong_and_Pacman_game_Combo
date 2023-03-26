#pragma once

#ifndef STATE_MAN_HPP
#define STATE_MAN_HPP

#include <memory>
#include <stack>

#include "State.h"

namespace Engine
{
	class StateManager
	{
	private:
		std::stack<std::unique_ptr<State>> mStateStack;
		std::unique_ptr<State> mNewState;

		bool mAdd = false, mReplace = false, mRemove = false;

	public:
		StateManager();
		~StateManager();

		void Add(std::unique_ptr<State> toAdd, bool Replace = false);
		void popCurrent();
		void processStateChange();
		std::unique_ptr<State>& getCurrent();
	};
} //Namespace Engine

#endif // STATE_MAN_HPP