#include <SFML/Window/Event.hpp>
#include "Header.h"
#include "PauseGame.h"

PauseGame::PauseGame(std::shared_ptr<Context>& context) : mContext(context)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{

    if (!font.loadFromFile("font/prstartk.ttf"))
    {
        std::cout << "Menu Font ARIAL not found" << std::endl;
    }
    //-----------------------------------------MENU--------------------------------------------------
    pauseText.setFont(font);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("Paused");
    pauseText.setPosition(sf::Vector2f(575, 350));
    pauseText.setScale(2, 3);
}

void PauseGame::ProcessInput()
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
            case sf::Keyboard::P:
            {
                mContext->mStates->popCurrent();
                std::cout << " I am unpaused " << std::endl;
                break;
            }
            //Pause game


            default:
                break;
            }
        }
    }
}

void PauseGame::Update(sf::Time deltaTime)
{
   // deltaTime.asMilliseconds();
}

void PauseGame::Draw()
{

    //Draw to the window
   // mContext->mWindow->clear();
    mContext->mWindow->draw(pauseText);
    mContext->mWindow->display();

}