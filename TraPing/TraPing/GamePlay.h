#pragma once

#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <memory>
#include "Game.h"
#include "State.h"


class GamePlay : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	//Add score
	sf::Text mScoreText;
	int mScore;

	sf::Time mElapsedTime;
	bool isPaused;
public:

	int blockVisited;
	int sss;



	GamePlay(std::shared_ptr<Context> mContext);
	~GamePlay();
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

	//Method
	void Pause() override;
	void Start() override;
};

#endif // GAME_PLAY_HPP
