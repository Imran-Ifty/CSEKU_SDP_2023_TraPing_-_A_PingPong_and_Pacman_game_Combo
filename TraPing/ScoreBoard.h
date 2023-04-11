#pragma once
#ifndef SCORE_BOARD
#define SCORE_BOARD

#include <SFML/Graphics/Text.hpp>

#include <memory>

#include "Game.h"
#include "State.h"
#include "Header.h"



class ScoreBoard : public Engine::State
{
private:
	std::shared_ptr<Context> mContext;
	sf::Text mDrawMapTitle;
	sf::RenderWindow &window;
	
	sf::Text User_Input, User_Name;
	sf::Font font1;  std::string sentence;
	std::map<std::string, int > Score;
	int size = Score.size();
	std::pair<int, std::string >Sorted_Score[1000];
	std::map<std::string, int > ::iterator it = Score.begin();
	int i = 0;
	sf::Text Desplay_Score_Word, Desplay_Name, Desplay_Score;
	std::string convert;
	std::ifstream scoreIn;
	std::ofstream scoreOut;
	
public:

	ScoreBoard(std::shared_ptr<Context>& context);
	~ScoreBoard();


	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
	void Text_Style(sf::Text& t, float Xposition, float Yposition, std::string s, sf::Color c, int font_size);
	void Keyboard_Handling(sf::Event& event, sf::RenderWindow& window);
	void Print_Score_Board(sf::RenderWindow& window);
	void  Save_Score_Board(int finale_score);

};

#endif // !SCORE_BOARD

