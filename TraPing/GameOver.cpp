#include <SFML/Window/Event.hpp>

#include "GameOver.h"
#include "GamePlay.h"

GameOver::GameOver(std::shared_ptr<Context>& context) : mContext(context), retryButtonSelected(true), retryButtonPressed(false), exitButtonSelected(false), exitButtonPressed(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{

    //Game over
//    mGameOverTitle.setFont(mContext->mAssets->getFont(AssetsID::E_Main_Font));
    if (!font1.loadFromFile("font/Squares.ttf"))
        std::cout << "Error" << std::endl;
    mGameOverTitle.setFont(font1);
    int i = 310;
    mGameOverTitle.setFont(font1);
    mGameOverTitle.setFillColor(sf::Color::Cyan);
    mGameOverTitle.setString("Game Over");
    mGameOverTitle.setPosition(sf::Vector2f(400, 128));
    mGameRetryButton.setCharacterSize(30);
    //Retry game

    mGameRetryButton.setFont(font1);
    mGameRetryButton.setFillColor(sf::Color::White);
    mGameRetryButton.setString("Retry");
    mGameRetryButton.setPosition(sf::Vector2f(600, i+50));
    mGameRetryButton.setCharacterSize(20);
    //Exit game


    mGameExitButton.setFont(font1);
    mGameExitButton.setFillColor(sf::Color::White);
    mGameExitButton.setString("Exit");
    mGameExitButton.setPosition(sf::Vector2f(600, i + 175));
    mGameExitButton.setCharacterSize(20);
}

void GameOver::ProcessInput()
{
    sf::Event event;

    while (mContext->mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mContext->mWindow->close();
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                //Keyboard control
            case sf::Keyboard::Up:
            {
                if (!retryButtonSelected)
                {
                    retryButtonSelected = true;
                    exitButtonSelected = false;
                }
                break;
            }

            case sf::Keyboard::Down:
            {
                if (!exitButtonSelected)
                {
                    retryButtonSelected = false;
                    exitButtonSelected = true;
                }
                break;
            }

            case sf::Keyboard::Return:
            {
                retryButtonPressed = false;
                exitButtonPressed = false;

                if (retryButtonSelected)
                {
                    retryButtonPressed = true;
                }
                else
                {
                    exitButtonPressed = true;
                }
                break;
            }

            default:
                break;
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{

    if (retryButtonSelected)
    {
        mGameRetryButton.setFillColor(sf::Color::Cyan);
        mGameExitButton.setFillColor(sf::Color::White);
    }

    else
    {
        mGameExitButton.setFillColor(sf::Color::Cyan);
        mGameRetryButton.setFillColor(sf::Color::White);
    }

    if (retryButtonPressed)
    {
        //Play state
        mContext->mStates->Add(std::make_unique<GamePlay>(mContext), true);
    }

    else if (exitButtonPressed)
    {
        mContext->mWindow->close();
    }
}

void GameOver::Draw()
{   
    mContext->mWindow->clear();
    //Draw to the window
    mContext->mWindow->draw(mGameOverTitle);
    mContext->mWindow->draw(mGameRetryButton);
    mContext->mWindow->draw(mGameExitButton);

    mContext->mWindow->display();
}