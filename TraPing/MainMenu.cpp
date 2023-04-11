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
	// main menu sound
	if (!buffer.loadFromFile("effect/menu.wav")) {
		// error handling
	}
	else {
		std::cout << " SOUND " << std::endl;
	}
	if (!bClick.loadFromFile("effect/click.wav")) {
		// error handling

		std::cout << " Error " << std::endl;
	}
	else {
	}
	if (!bPressed.loadFromFile("effect/pressed.wav")) {
		// error handling
		std::cout << " Error " << std::endl;
	}
	else {
	}

	menuSound.setBuffer(buffer); // menu sound
	mClick.setBuffer(bClick);
	mPressed.setBuffer(bPressed);

	menuSound.play();
	menuSound.getLoop();

	// main menu click sound




	if (!font1.loadFromFile("font/Squares.ttf"))
		std::cout << "Error" << std::endl;


	// backgroud 
	if (!tBackgr.loadFromFile("img/bg.jpg")) {
		std::cout << "not Backgroud " << std::endl;
	}
	
	// Create a sprite to display the background image
	sBackgr.setTexture(tBackgr);
	// Set the background sprite to cover the entire window
	sBackgr.setScale(
		float(mContext->mWindow->getSize().x) / sBackgr.getTexture()->getSize().x,
		float(mContext->mWindow->getSize().y) / sBackgr.getTexture()->getSize().y
	);



	mGameTitle.setFont(font1);
	mGameTitle.setPosition(370, 80);
	mGameTitle.setFillColor(sf::Color::Cyan);
	mGameTitle.setStyle(sf::Text::Bold);
	mGameTitle.setCharacterSize(45);
	mGameTitle.setString("TraPing");  //To print word "Score"
	
	if (!font.loadFromFile("font/prstartk.ttf"))
	{
		std::cout << "Menu Font ARIAL not found" << std::endl;
	}
	//-----------------------------------------MENU--------------------------------------------------
	int i = 310;
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Start Game");
	menu[0].setPosition(sf::Vector2f(575, i));


	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Ladder Board");
	menu[1].setPosition(sf::Vector2f(575,i*1.3));


	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Draw your Maze");
	menu[2].setPosition(sf::Vector2f(575, i*1.6));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(575, i*1.9));
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
				mClick.play();
				break;

			case sf::Keyboard::Down:

				mClick.play();
				MoveDown();
				break;
			
			// game setting browser
			case sf::Keyboard::Return:

				switch (GetPressedItem())
				{
				case 0:                        
					// start game

					std::cout << "I am in Game" << std::endl;
					mPressed.play();
					menuSound.stop();
					loadMap();
					mContext->mStates->Add(std::make_unique<GamePlay>(mContext), true);
				
					break;

				case 1:
					std::cout << "Score Board" << std::endl;
					mPressed.play();
					menuSound.stop();
					mContext->mStates->Add(std::make_unique<ScoreBoard>(mContext), true);
					
					break;

				case 2:

					std::cout << " Draw Maps " << std::endl;
					mPressed.play();
					menuSound.stop();
					mContext->mStates->Add(std::make_unique<DrawMap>(mContext), true);
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
	//mContext->mWindow->draw(sBackgr);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		mContext->mWindow->draw(menu[i]);
	}
	mContext->mWindow->draw(mGameTitle);
	mContext->mWindow->display();
}



//----------------------------------(Functions to Control on The Start Screen )----------
void MainMenu::MoveUp()
{
	
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}
void MainMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}

void MainMenu::loadMap()
{
	int maze[50][50];
	int rows = 28, cols = 28;
	std::fstream inputStream;
	inputStream.open("map/map.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			inputStream >> maze[i][j];
		}
	}
	inputStream.close();

	std::ofstream outfile;
	outfile.open("map/map1.txt", std::ios::out);
	outfile.clear();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			outfile << maze[i][j] << " ";
		outfile << "\n";
	}
	outfile.close();
}
