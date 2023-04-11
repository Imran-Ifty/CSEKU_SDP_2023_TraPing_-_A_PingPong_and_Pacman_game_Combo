#include "StateManager.h"

Engine::StateManager::StateManager() : mAdd(), mReplace(), mRemove()
{
}

Engine::StateManager::~StateManager()
{
}

void Engine::StateManager::Add(std::unique_ptr<State> toAdd, bool Replace)
{
    mAdd = true;
    mNewState = std::move(toAdd);
    mReplace = Replace;
}

void Engine::StateManager::popCurrent()
{
    mRemove = true;
}

void Engine::StateManager::processStateChange()
{
    if (mRemove && (!mStateStack.empty()))
    {
        mStateStack.pop();

        if (!mStateStack.empty())
        {
            mStateStack.top()->Start();
        }
        mRemove = false;
    }

    if (mAdd)
    {
        if (mReplace && (!mStateStack.empty()))
        {
            mStateStack.pop();
            mReplace = false;
        }

        if (!mStateStack.empty())
        {
            mStateStack.top()->Pause();
        }

        mStateStack.push(std::move(mNewState));
        mStateStack.top()->Init();
        mStateStack.top()->Start();
        mAdd = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateManager::getCurrent()
{
    return mStateStack.top();
}