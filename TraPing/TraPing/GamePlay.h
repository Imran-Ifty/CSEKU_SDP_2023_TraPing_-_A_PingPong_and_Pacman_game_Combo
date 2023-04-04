#pragma once

#ifndef GAME_PLAY_HPP
#define GAME_PLAY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <memory>
#include "Game.h"
#include "Player.h"
#include "State.h"




class GamePlay : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	//Add score
	sf::Text mScoreText , mGameTitle;
	sf::Texture tHero;
	sf::Sprite sHero;
	int mScore ,rows , cols;
	//float speed = 100.0f;
	sf::Clock clock , powerUpTimer;
	sf::Vector2f movement;
	float time;

	sf::Time mElapsedTime;
	bool isPaused;
	// main screen assest
	// Texture backGround, pac, wall, blinky, dot, bigdot, pink;

	sf::Texture backGround, pac, wall, blinky, dot, bigdot, pink;
	sf::Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkSprite;
	sf::Texture playerTexture;
	sf::Sprite player;
	// side screen assets
	sf::Text  text_score, text, control, control1, control2, control3, control4;
	sf::Font font, fon, fo ,sideTitleFont;
	std::string s;

	// for player movement
	int Besh_x = 0, Besh_y = 0;
	int dirX = 0, dirY = 0 , Dir ;
	int speed; // player speed
	bool move_ch; 
	float playerSpeed = 32.0f;
	int points = 0;

	//Player pp;

public:
	sf::Vector2f playerPos;
	const int ts = 32;
	int blockVisited;
	int sss;
	bool hasPowerUp = false;
	bool Game = true;
	std::stack<std::pair<int, int>> stack;
	bool left, right;
	int x = 2, y = 14; // player init position
	int dx = 0, dy = 0 , maze1[50][50];
	float timer = 0, delay = 0.07;
	GamePlay(std::shared_ptr<Context> mContext);
	~GamePlay();
	//void drop(int y, int x);
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
	//Method
	void Pause() override;
	void Start() override;

	int pac_diffPOS(int Next_moving);

	struct Enemy
	{
		int x, y, dx, dy;

		Enemy()
		{
			x = y = 450 ;
			dx = 5 - rand() % 8;
			dy = 5 - rand() % 8;
		}

		void move(int maze1[][50], int ts)
		{
			x += dx;
			if (maze1[y / ts][x / ts] == 1)
			{
				dx = -dx;
				x += dx;
			}
			y += dy;
			if (maze1[y / ts][x / ts] == 1)
			{
				dy = -dy;
				y += dy;
			}
		}
	}enemy[50];

};

#endif // GAME_PLAY_HPP
