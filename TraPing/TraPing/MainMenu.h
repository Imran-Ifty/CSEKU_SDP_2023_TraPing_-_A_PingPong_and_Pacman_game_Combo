#pragma once

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#define MAX_NUMBER_OF_ITEMS 4
#include "Header.h"

#include "Game.h"
#include "State.h"

class MainMenu : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	sf::Text mGameTitle, mGamePlayButton, mGameExitButton;

	sf::View view;

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	bool playButtonSelected = true, playButtonPressed = false;
	bool exitButtonSelected = false, exitButtonPressed = false;
	sf::Font font;
	int selectedItemIndex;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

public:
	MainMenu(std::shared_ptr<Context>& context);
	~MainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override; //Same as zero
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

};

#endif // MAIN_MENU_HPP