#include <SFML/Window/Event.hpp>

#include <cstdlib>
#include <ctime>

#include "GameOver.h"
#include "GamePlay.h"
#include "PauseGame.h"
#include <iostream>
#include "MainMenu.h"


struct MAP {
	std::string map1 = "map/map1.txt";
	std::string map2 = "map/map2.txt";
	std::string map3 = "map/map3.txt";
	std::string map4 = "map/map4.txt";

}MAP;

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
	// init the MAPS path as map1 , map2 , map3
	// row init 
	rows = 28, cols = 28;

	// map init
	std::fstream inputStream;
	switch (level) {
	case 1:
		inputStream.open(MAP.map1);
		break;
	case 2:
		inputStream.open(MAP.map2);
		break;
	case 3:
		inputStream.open(MAP.map3);
		break;

	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			inputStream >> maze1[i][j];

	inputStream.close();

	// set a view 
	sf::View view(sf::FloatRect(0, 0, mContext->mWindow->getSize().x, mContext->mWindow->getSize().y));
	view.setCenter(mContext->mWindow->getSize().x / 2, mContext->mWindow->getSize().y / 2);
	mContext->mWindow->setView(view);

	std::cout << " I am in Game " << std::endl;;

	// init the fonts
	if (!font.loadFromFile("font/Kaph-Regular.ttf"))
		std::cout << "Error" << std::endl;

	if (!sideTitleFont.loadFromFile("font/Squares.ttf"))
		std::cout << "Error" << std::endl;

	mGameTitle.setFont(sideTitleFont);
	mGameTitle.setPosition(1020, 30);
	mGameTitle.setFillColor(sf::Color::Cyan);
	mGameTitle.setStyle(sf::Text::Bold);
	mGameTitle.setCharacterSize(25);
	mGameTitle.setString("TraPing");

	// score text rendering
	text_score.setFont(font);
	text_score.setPosition(1080, 128);
	text_score.setFillColor(sf::Color::Cyan);
	text_score.setStyle(sf::Text::Bold);
	text_score.setCharacterSize(60);
	text_score.setString("Score : ");  //To print word "Score"

	text.setFont(font);
	text.setPosition(1400, 150); //1248
	text.setFillColor(sf:: Color::Cyan);
	text.setStyle(sf::Text::Bold);
	text.setString(s);                 //To print the score 


	control.setFont(font);
	control.setPosition(1056, 416);
	control.setFillColor(sf::Color::White);
	control.setStyle(sf::Text::Bold);
	control.setCharacterSize(45);
	control.setString("Controls ");

	control1.setFont(font);
	control1.setPosition(960, 480);
	control1.setFillColor(sf::Color::Green);
	control1.setString("Arrow Keys to move around");

	control2.setFont(font);
	control2.setPosition(960, 544);
	control2.setFillColor(sf::Color::Green);
	control2.setString("P --> Pause/UnPause");

	control3.setFont(font);
	control3.setPosition(960, 608);
	control3.setFillColor(sf::Color::Green);
	control3.setString("M --> Mute/UnMute Sound");

	control4.setFont(font);
	control4.setPosition(960, 672);
	control4.setFillColor(sf::Color::Green);
	control4.setString("Esc --> Exit ");


	/* Player & character Buildup and init*/

//	player.setTexture(playerTexture);
	if (!playerTexture.loadFromFile("img/blinky.png")) {
		std::cout << "Player image not found !!! " << std::endl;
	}
	player.setTexture(playerTexture);
	player.setPosition(x * 32, y * 32);



	if (!tHero.loadFromFile("img/g1.png")) {
		std::cout << "Hero image not found !!! " << std::endl;
	}
	// our hero is here 
	sHero.setTexture(tHero);
	sHero.setPosition(sf::Vector2f(448, 704));
	sHero.setTextureRect(sf::IntRect(0, 0, 32, 32));
	sHero.setOrigin(16, 16);

	// wall sprite 
	wall.loadFromFile("img/wall.jpg");                              // Wall
	wallSprite.setTexture(wall);

	// big dot 
	bigdot.loadFromFile("img/bigdot.png");                        // big dot
	bigdotSprite.setTexture(bigdot);

	// point dot sprite
	if (!dot.loadFromFile("img/dot.png")) {							// just a dot
		std::cout << " Not Allocated " << std::endl;
	}
	dotSprite.setTexture(dot);
	dotSprite.setColor(sf::Color::Green);

	// sound design 
	
	if (!bGamePlay.loadFromFile("effect/gameSong.wav")) {
			// error handling
	}
	else {
		std::cout << " SOUND " << std::endl;
	}

	if (!bDot.loadFromFile("effect/point.wav")) {
		// error handling
	}
	else {
		std::cout << " SOUND " << std::endl;
	}

	mDot.setBuffer(bDot);
	mGamePlay.setBuffer(bGamePlay);
	mGamePlay.play();
	mGamePlay.setLoop(true);

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
		if (event.type == sf::Event::KeyPressed) {

			switch (event.key.code)
			{
			case sf::Keyboard ::M:
				if (mute == false) {
					mute = true;
				}
				else {
					mute = false;
				}
				break;
			case sf::Keyboard::Up:
				std::cout << " Up " << std::endl;
				if (y > 1 && maze1[y - 1][x] != 1) {
					y--;
					player.move(0, -32);
					dirY = -1;
				}
				break;

			case sf::Keyboard::Down:
				if (y < 28 - 2 && maze1[y + 1][x] != 1) {
					y++;
					player.move(0, 32);
					dirY = 1;
				}
				std::cout << " Down " << std::endl;
				break;

			case sf::Keyboard::Left:

				if (x > 1 && maze1[y][x-1] != 1)
				{
					x--;
					player.move(-32, 0);
					dirX = -1;
				}				
				std::cout << " Left " << std::endl;
				break;

			case sf::Keyboard::Right:
			    if (x < GRID_WIDTH - 2 && maze1[y][x + 1] != 1) {
					x++;
					player.move(32, 0);
					dirX = 1;
				}
			
				right = true;
				std::cout << " Right " << std::endl;

				break;

			case sf::Keyboard::Escape:
				mGamePlay.stop();
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

	if (maze1[y][x] == 3) { // 3 for fruits: when player eats a fruit he will have power like Wall making for 5 seconds
		hasPowerUp = true;
		powerUpTimer.restart();
		// remove the fruit from the grid
		maze1[y][x] = 0; // 0 for empty plane
		points += 20;
	}
	if (maze1[y][x] == 2) { // points
		points = points + 10;
		maze1[y][x] = 0;
		if(!mute)
			mDot.play();
	}
	if (hasPowerUp && powerUpTimer.getElapsedTime().asSeconds() >= 5.0f) {
		hasPowerUp = false;
	}
	std::string s = std::to_string(points);
	text.setString(s);

	mContext->mWindow->clear();

}

void GamePlay::Update(sf::Time deltaTime)
{
	//std::cout << " I am in GamePlay Update" << std::endl;

	// draw the maps 


	for (int i = 0; i < 10; i++) {
		enemy[i].move(maze1, ts); // ts = tile size
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int pacx = sHero.getPosition().x / 32, pacy = sHero.getPosition().y / 32;
			if (maze1[i][j] == 1)
			{
				wallSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				wallSprite.setPosition(j * 32, i * 32);
				mContext->mWindow->draw(wallSprite);
			}
			else if (maze1[i][j] == 2)
			{
				//win = false;
				dotSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
				dotSprite.setColor(sf::Color::Red);
				dotSprite.setPosition(j * 32 + 8, i * 32 + 8);
				mContext->mWindow->draw(dotSprite);
				if (pacx == j && pacy == i)
				{
					maze1[i][j] = 0;
					//score += 10;  //Abnb 
					//if (eatdot.getStatus() == Music::Status::Stopped)
						//eatdot.play();
				}
			}
			else if (maze1[i][j] == 3)
			{
				//win = false;
				bigdotSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				bigdotSprite.setPosition(j * 32, i * 32);
				mContext->mWindow->draw(bigdotSprite);
				if (pacx == j && pacy == i)
				{
					maze1[i][j] = 0;
					//fright = 1000;
					//score += 50;  //Abnb 
					//if (eatbigdot.getStatus() == Music::Status::Stopped)
						//eatbigdot.play();
				}
			}

		}
	}


	// Player Moving 
	sf::Vector2f playerPos = player.getPosition();
	//std::cout << " X : " << (playerPos.x / 32) + 1 << "  Y: " << (playerPos.y / 32) + 1 << std::endl;
	int px = (playerPos.x / 32) + 1, py = (playerPos.y / 32) + 1;
	int prex = playerPos.x / 32, prey = playerPos.y / 32;
	if (maze1[py-1][px-1] == 1) {
		std::cout << " WALL" << std::endl;
	}



	// player power up 

	if (hasPowerUp && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		// get the player's current grid position
		int playerX = player.getPosition().x / 32;
		int playerY = player.getPosition().y / 32;
		// place a wall in the next grid cell in the player's direction
		int nextX = playerX + dirX;
		int nextY = playerY + dirY;
		if (nextX >= 0 && nextX < 28 && nextY >= 0 && nextY < 28
			&& maze1[nextY][nextX] == 0) {
			maze1[nextY][nextX] = 1; // 1 for wall
			// play a sound effect
			//placeWallSound.play();
		}
	}


	// check if all fruits are gone
	check = 0;
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			if (maze1[i][j] == 2) {
				check++;
			}
		}
	}
	if (check == 0) 
	{
		level++;
		std::cout << " End " << std::endl;
	}
	
}
void GamePlay::Draw()
{
//	mContext->mWindow->clear();

	for (int i = 0; i < 10; i++)
	{
		sHero.setPosition(enemy[i].x, enemy[i].y);
		mContext->mWindow->draw(sHero);
		if (player.getGlobalBounds().intersects(sHero.getGlobalBounds())) {
			std::cout << " i am collide " << std::endl;
			//mContext->mStates->Add(std::make_unique<GameOver>(mContext));
			
		}
	}
	mContext->mWindow->draw(player);
	mContext->mWindow->draw(text); //ok
	mContext->mWindow->draw(text_score);//ok
	mContext->mWindow->draw(control);
	mContext->mWindow->draw(control1);
	mContext->mWindow->draw(control2);
	mContext->mWindow->draw(control3);
	mContext->mWindow->draw(control4);
	//mContext->mWindow->draw(sHero);


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


// player 


int GamePlay::pac_diffPOS(int Next_moving)
{
	int Next_tile = 0;
	if (Next_moving > 0)  Next_tile = 32;
	else if (Next_moving < 0)  Next_tile = -32;
	else Next_tile = 0;

	return Next_tile;
}


