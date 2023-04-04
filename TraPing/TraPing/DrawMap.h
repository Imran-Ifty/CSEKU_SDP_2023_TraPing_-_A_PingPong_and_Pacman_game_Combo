#pragma once

#ifndef DRAW_MAP_HPP
#define DRAW_MAP_HPP

#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "Game.h"
#include "State.h"
#include "Header.h"

class DrawMap : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	sf::Text mDrawMapTitle;
	int *maze1[50][50];

	sf::Font font1;
	sf::Texture backGround, pac, wall, blinky, dot, bigdot, pink;
	sf::Sprite  backGroundsprite, pacSprite, wallSprite, blinkySprite, dotSprite, bigdotSprite, pinkSprite;

	sf::Texture backgr, lives_pacman1, lives_pacman2, lives_pacman3, lives_pacman4, lives_pacman5, inky, clyde;
	sf::Sprite  backgr_score, lives_pacman_sprite1, lives_pacman_sprite2, lives_pacman_sprite3, lives_pacman_sprite4, lives_pacman_sprite5, inkySprite, clydeSprite;

	sf::RenderWindow& window;

public:
	int rows;
	int cols;
	int drawmaze[50][50];
	std::fstream inputStream;
	sf::Texture textur;
	sf::Sprite sprite;


	DrawMap(std::shared_ptr<Context>& context);
	~DrawMap();


	void aa();
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};

#endif // DRAW_MAP_HPP