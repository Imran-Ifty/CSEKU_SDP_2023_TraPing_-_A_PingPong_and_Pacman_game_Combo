#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include "StateManager.h"

class Context
{
public:
	std::unique_ptr<Engine::StateManager> mStates;
	std::unique_ptr<sf::RenderWindow> mWindow;
	//int maze[50][50];

	Context()
	{
		mStates = std::make_unique<Engine::StateManager>();
		mWindow = std::make_unique<sf::RenderWindow>();
	//	int maze[50][50]{};
	}
};

class Game
{
private:
	std::shared_ptr<Context> mContext;
	const sf::Time _timePerFrame = sf::seconds(1.f / 60.f); // 60 fps

public:
	Game();
	~Game();

	void RunGame();
};

#endif // GAME_HPP