#include "Header.h"

#include "GamePlay.h"
#include "MainMenu.h"
#include "DrawMap.h"

#include "ScoreBoard.h"


MainMenu::MainMenu(std::shared_ptr<Context>& context) : mContext(context), playButtonSelected(), playButtonPressed(), exitButtonSelected(), exitButtonPressed()
{

}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{

	std::cout << "asd " << std::endl;

	
	if (!font.loadFromFile("font/prstartk.ttf"))
	{
		std::cout << "Menu Font ARIAL not found" << std::endl;
	}
	//-----------------------------------------MENU--------------------------------------------------
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Start Game");
	menu[0].setPosition(sf::Vector2f(575, 900 / (MAX_NUMBER_OF_ITEMS + 1) * 1));


	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Ladder Board");
	menu[1].setPosition(sf::Vector2f(575, 900 / (MAX_NUMBER_OF_ITEMS + 1) * 1.7));


	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Draw your Maze");
	menu[2].setPosition(sf::Vector2f(575, 900 / (MAX_NUMBER_OF_ITEMS + 1) * 2.3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(575, 900 / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu[i].setScale(1, 2);
	}
	selectedItemIndex = 0;

}
void MainMenu::ProcessInput()
{
	sf::Event event;
	while (mContext->mWindow->pollEvent(event))
	{

		switch (event.type)
		{
			//---------------------(Control on Moving in The start Menu  )-------------------
		case sf::Event::KeyReleased:

			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				MoveUp();
				break;

			case sf::Keyboard::Down:
				MoveDown();
				break;
				//----------------------------------(Control on The Return value )---------------------------
			case sf::Keyboard::Return:

				switch (GetPressedItem())
				{
				case 0:                        // start game

					std::cout << "I am in Game" << std::endl;
					mContext->mStates->Add(std::make_unique<GamePlay>(mContext), true);
					//startScreen.close();
					//gamefn(2);
					break;

				case 1:
					std::cout << "Score Board" << std::endl;
					mContext->mStates->Add(std::make_unique<ScoreBoard>(mContext), true);
					//startScreen.close();      // open setting
					//scoreBoardfn();
					break;

				case 2:

					std::cout << " Draw Maps " << std::endl;

					mContext->mStates->Add(std::make_unique<DrawMap>(mContext), true);
					//startScreen.close();
					//draw_your_maze();                // maze 
					break;

				case 3:
					exit(0);                 // exit game 
					break;
				}
				break;
			}
			break;
			//---------------------------------------------------------------------------
		case sf::Event::Closed:
			mContext->mWindow->close();
			break;
			//---------------------------------------------------------------------------
		}
	}

	
	
}

void MainMenu::Update(sf::Time deltaTime)
{
   

}

void MainMenu::Draw()
{
	mContext->mWindow->clear();
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		mContext->mWindow->draw(menu[i]);
	}
	mContext->mWindow->display();
}



//----------------------------------(Functions to Control on The Start Screen )----------
void MainMenu::MoveUp()
{
	
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
	}
}
void MainMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
	}
}