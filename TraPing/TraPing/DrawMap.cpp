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

	bigdot.loadFromFile("img/bigdot.png");                        // big dot
	bigdotSprite.setTexture(bigdot);


	wall.loadFromFile("img/wall.jpg");                              // Wall
	wallSprite.setTexture(wall);

	pac.loadFromFile("img/sheet.png");                            // PacmMan
	pacSprite.setTexture(pac);
	pacSprite.setPosition(sf::Vector2f(448, 704));
	pacSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	blinky.loadFromFile("img/blinky.png");                          // Blinky
	blinkySprite.setTexture(blinky);
	blinkySprite.setPosition(sf::Vector2f(384, 416));
	blinkySprite.setTextureRect(sf::IntRect(0, 0, 28, 28));


	pink.loadFromFile("img/g3.png");
	pinkSprite.setTexture(pink);									// pinky 
	pinkSprite.setPosition(sf::Vector2f(416, 416));
	pinkSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	inky.loadFromFile("img/g1.png");
	inkySprite.setTexture(inky);									// inky 
	inkySprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	inkySprite.setPosition(sf::Vector2f(448, 416));

	clyde.loadFromFile("img/g4.png");
	clydeSprite.setTexture(clyde);									// clyde
	clydeSprite.setPosition(sf::Vector2f(480, 416));
	clydeSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));


	drawmaze[50][50] = {0};
	inputStream.open("maps/drawurmaze.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			inputStream >> drawmaze[i][j];
		}
	}

	textur.loadFromFile("img/drawurmaze.png");
	sprite.setTexture(textur);
	sprite.setPosition(896, 0);




}

void DrawMap::ProcessInput()
{
	sf::Event event;
	while (mContext->mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mContext->mWindow->close();

		else if (event.text.unicode == 27) //27 Esc button
		{

			std::cout << " Back on the main Menu" << std::endl;
			mContext->mStates->Add(std::make_unique<MainMenu>(mContext), true);
			break;
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					//maze1[i][j] = drawmaze[i][j];

			std::cout << "I am in Game" << std::endl;
			mContext->mStates->Add(std::make_unique<GamePlay>(mContext), true);
		}
	}
	
}

void DrawMap::Update(sf::Time deltaTime)
{
	int b = sf::Mouse::getPosition(window).x / 32, a = sf::Mouse::getPosition(window).y / 32;
	if (drawmaze[a][b] != 4 && drawmaze[a][b] != 6 && a != 0 && b != 0 && a != 27 && b != 27)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			drawmaze[a][b] = 2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			drawmaze[a][b] = 3;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			drawmaze[a][b] = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			drawmaze[a][b] = 0;
	}

	window.clear();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{

			if (drawmaze[i][j] == 1)
			{
				wallSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				wallSprite.setPosition(j * 32, i * 32);
				window.draw(wallSprite);

				std::cout << "Wall" << std::endl;
			}
			else if (drawmaze[i][j] == 2)
			{
				dotSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				dotSprite.setColor(sf::Color::Red);
				dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
				window.draw(dotSprite);
			}
			else if (drawmaze[i][j] == 3)
			{
				bigdotSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				bigdotSprite.setPosition(j * 32, i * 32);
				window.draw(bigdotSprite);
			}
		}

}

void DrawMap::Draw()
{
   // mContext->mWindow->clear();
    //Draw to the window
	window.draw(blinkySprite);
	window.draw(pinkSprite);
	window.draw(inkySprite);
	window.draw(clydeSprite);
	window.draw(pacSprite);
	window.draw(sprite);
	window.display();

}