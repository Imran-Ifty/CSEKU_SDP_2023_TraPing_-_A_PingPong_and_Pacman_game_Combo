#include <SFML/Window/Event.hpp>

#include <cstdlib>
#include <ctime>

#include "GameOver.h"
#include "GamePlay.h"
#include "PauseGame.h"
#include <iostream>
#include "MainMenu.h"

GamePlay::GamePlay(std::shared_ptr<Context> context) :
	mContext(context),
	mElapsedTime(sf::Time::Zero),
	isPaused(false)
{
	mScore = 0;
}

GamePlay::~GamePlay()
{
}


void GamePlay::Init()
{
	sf::View view(sf::FloatRect(0, 0, mContext->mWindow->getSize().x, mContext->mWindow->getSize().y));
	view.setCenter(mContext->mWindow->getSize().x / 2, mContext->mWindow->getSize().y / 2);
	mContext->mWindow->setView(view);

	std::cout << " I am in Game " << std::endl;;

}


void GamePlay::ProcessInput()
{
	sf::Event event;

	while (mContext->mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mContext->mWindow->close();
		}
		if (event.type == sf::Event::KeyPressed)

			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				 std::cout << " Up " << std::endl;
				break;

			case sf::Keyboard::Down:
				std::cout << " Down " << std::endl;
				break;

			case sf::Keyboard::Left:
				std::cout << " Left " << std::endl;
				break;

			case sf::Keyboard::Right:
				std::cout << " Right " << std::endl;

				break;
			case sf::Keyboard::Escape:
				mContext->mStates->Add(std::make_unique<MainMenu>(mContext));
				break;

				//Pause game
			case sf::Keyboard::P:
				mContext->mStates->Add(std::make_unique<PauseGame>(mContext));
				break;

			default:
				break;
			}
	}


}

void GamePlay::Update(sf::Time deltaTime)
{


	//std::cout << " I am in GamePlay Update" << std::endl;
}

void GamePlay::Draw()
{
	mContext->mWindow->clear();
	mContext->mWindow->display();
}

void GamePlay::Pause()
{
	isPaused = true;
}

void GamePlay::Start()
{
	isPaused = false;
}

