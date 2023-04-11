#pragma once

#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "Game.h"
#include "State.h"

class GameOver : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	sf::Text mGameOverTitle, mGameRetryButton, mGameExitButton;
	sf::Font font1, font2;

	bool retryButtonSelected, retryButtonPressed;
	bool exitButtonSelected, exitButtonPressed;

public:
	GameOver(std::shared_ptr<Context>& context);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};

#endif // GAME_OVER_HPP