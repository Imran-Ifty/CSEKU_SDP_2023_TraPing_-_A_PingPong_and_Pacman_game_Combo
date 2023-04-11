#include "DrawMap.h"
#include "MainMenu.h"
#include "GamePlay.h"

DrawMap::DrawMap(std::shared_ptr<Context>& context) : mContext(context), window(*mContext->mWindow)
{
}

DrawMap::~DrawMap()
{
}

void DrawMap::Init()
{
	// declare the row and cols
	rows = 28;
	cols = 28;

	// font of title side
	if (!font1.loadFromFile("font/Squares.ttf"))
		std::cout << "Error" << std::endl;


	// Apple sprites 
	if (!bigdot.loadFromFile("img/bigdot.png")) {
		std::cout << " Not Allocated " << std::endl;
	}                       // big dot
	bigdotSprite.setTexture(bigdot);

	// point dot sprite
	if (!dot.loadFromFile("img/dot.png")) {
			std::cout << " Not Allocated " << std::endl;
	}                      
	dotSprite.setTexture(dot);

	// wall sprite 
	wall.loadFromFile("img/wall.jpg");
	wallSprite.setTexture(wall);


	//drawmaze[50][50] = {0}; // blank screen to draw a map
	inputStream.open("map/drawurmaze.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			inputStream >> drawmaze[i][j];
		}
	}
	inputStream.close();

	// Side Title 
	mDrawMapTitle.setFont(font1);
	mDrawMapTitle.setPosition(1020, 30);
	mDrawMapTitle.setFillColor(sf::Color::Cyan);
	mDrawMapTitle.setStyle(sf::Text::Bold);
	mDrawMapTitle.setCharacterSize(25);
	mDrawMapTitle.setString("TraPing");

	// side note and instruction
	textur.loadFromFile("img/drawurmaze.png");
	sprite.setTexture(textur);
	sprite.setPosition(896, 200); //896, 0 

}

void DrawMap::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			std::ofstream outfile;
			outfile.open("filename.txt", std::ios::out);
			outfile.clear();
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++)
					outfile << drawmaze[i][j] << " ";
				outfile << "\n";
			}
			outfile.close();
			std::cout << "done";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::cout << " Back on the main Menu" << std::endl;
			mContext->mStates->Add(std::make_unique<MainMenu>(mContext), true);
			break;

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			std::ofstream outfile;
			outfile.open("map/map1.txt", std::ios::out);
			outfile.clear();
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++)
					outfile << drawmaze[i][j] << " ";
				outfile << "\n";
			}
			std::cout << " Copy Done " << std::endl;
			outfile.close();
			std::cout << "I am in Game" << std::endl;
			mContext->mStates->Add(std::make_unique<GamePlay>(mContext), true);

		}
	}
}

void DrawMap::Update(sf::Time deltaTime)
{

	int b = sf::Mouse::getPosition(window).x / 32, a = sf::Mouse::getPosition(window).y / 32;
	std::cout << " A : " << a << "  B : " << b << std::endl;
	if (drawmaze[a][b] != 4 && drawmaze[a][b] != 6 && a != 0 && b != 0 && a != 27 && b != 27)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			drawmaze[a][b] = 2; // 
			std::cout << " small points " << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) // big dot
		{
			drawmaze[a][b] = 3;
			std::cout << " Big Dot " << std::endl;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		{
			drawmaze[a][b] = 1; // wall
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  // remove 
			drawmaze[a][b] = 0;
		}
	}
	
}

void DrawMap::Draw()
{
	window.clear();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{

			if (drawmaze[i][j] == 1)
			{
				wallSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				wallSprite.setPosition(j * 32, i * 32);
				window.draw(wallSprite);
			}
			else if (drawmaze[i][j] == 2) // 2 for point 
			{
				dotSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				dotSprite.setColor(sf::Color::Green);
				dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
				window.draw(dotSprite);
			}
			else if (drawmaze[i][j] == 3) // 3 for apple
			{
				bigdotSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				bigdotSprite.setPosition(j * 32, i * 32);
				window.draw(bigdotSprite);
			}
		}
	
	window.draw(mDrawMapTitle);
	window.draw(sprite);
	window.display();
}