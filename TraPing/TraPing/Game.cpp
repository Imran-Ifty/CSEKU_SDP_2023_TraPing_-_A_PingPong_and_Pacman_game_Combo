#include "Game.h"
#include "MainMenu.h"

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;


Game::Game() :
	mContext(std::make_shared<Context>())
{
	//Render the snake game
	mContext->mWindow->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TraPing");

	// Go to main menu state
	mContext->mStates->Add(std::make_unique<MainMenu>(mContext));
}

Game::~Game()
{
}

void Game::RunGame()
{
	sf::Clock clock;

	sf::Time timeSinceLastFrame = sf::Time::Zero;

	while (mContext->mWindow->isOpen())
	{
		timeSinceLastFrame += clock.restart();

		while (timeSinceLastFrame > _timePerFrame)
		{
			(timeSinceLastFrame -= _timePerFrame);

			mContext->mStates->processStateChange();
			mContext->mStates->getCurrent()->ProcessInput();
			mContext->mStates->getCurrent()->Update(_timePerFrame);
			mContext->mStates->getCurrent()->Draw();
		}
	}
}
