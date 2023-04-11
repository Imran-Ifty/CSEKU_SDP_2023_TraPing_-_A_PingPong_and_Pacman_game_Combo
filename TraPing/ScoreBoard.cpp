#include "ScoreBoard.h"
#include "MainMenu.h"

ScoreBoard::ScoreBoard(std::shared_ptr<Context>& context) : mContext(context) , window(*mContext->mWindow)
{
}

ScoreBoard::~ScoreBoard()
{
}



void ScoreBoard::Init()
{
	scoreIn.open("score/Score.txt");

	//--------- Read score from file --------------------//
	if (scoreIn.fail())
	{
		std::cerr << "Error while opening ifstream\n";
		exit(1);
	}

	while (!scoreIn.eof())
	{
		std::pair<std::string, int > name_and_score;
		scoreIn >> name_and_score.first;
		if (scoreIn.fail() || name_and_score.first[0] == '0')
			scoreIn >> name_and_score.first;

		scoreIn >> name_and_score.second;
		if (scoreIn.fail())
			scoreIn >> name_and_score.second;
		//	scoreIn >> name_and_score.first >> name_and_score.second;
		Score[name_and_score.first] = name_and_score.second;

	}
	scoreIn.close();

	//----------------- sort score ascending order ---------------//

	size = Score.size();
	it = Score.begin();
	for (; it != Score.end(); it++, i++)
	{
		Sorted_Score[i].first = it->second;
		Sorted_Score[i].second = it->first;
	}

	sort(Sorted_Score, Sorted_Score + size);
	Score.clear();
	for (int i = 0; i < size; i++)
	{
		Score[Sorted_Score[i].second] = Sorted_Score[i].first;
		//Sorted_Score[i].first = it->second;
		//Sorted_Score[i].second = it->first;
	}
}

void ScoreBoard::ProcessInput()
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
	}
}

void ScoreBoard::Update(sf::Time deltaTime)
{
}

void ScoreBoard::Draw()
{
    //mContext->mWindow->clear();
	 window.clear();
	//Draw to the window
	this->Print_Score_Board(window);
    //mContext->mWindow->display();
	 window.display();

}

void ScoreBoard::Text_Style(sf::Text& t, float Xposition, float Yposition, std::string s, sf::Color c, int font_size)
{
	if (!font1.loadFromFile("font/PixeloidSans.ttf"))
		std::cout << "Error" << std::endl;

	t.setFont(font1);
	t.setCharacterSize(font_size);
	t.setFillColor(c);
	t.setStyle(sf::Text::Bold);
	t.setString(s);
	t.setPosition(Xposition, Yposition);
}

void ScoreBoard::Save_Score_Board(int finale_score)
{
	scoreOut.open("Score/Score.txt");
	Score[sentence] =std:: max(finale_score, Score[sentence]);

	scoreOut.clear();
	it = Score.begin();
	for (; it != Score.end(); it++)
	{
		//cout << it->first << " " << it->second << endl;
		scoreOut << it->first << " " << it->second << " ";
	}
	scoreOut.close();
}

void ScoreBoard::Print_Score_Board(sf::RenderWindow& wind)
{
	float x = 600.0, y = 0;
	Text_Style(Desplay_Score_Word, x, y, "Score", sf::Color::Cyan, 100);
	x = 470.0; y = 120.0;
	wind.draw(Desplay_Score_Word);
	for (i = size - 1; i >= 0; i--, y += 90)
	{
		if (Sorted_Score[i].second == "")
			break;

		convert = std::to_string(Sorted_Score[i].first);

		Text_Style(Desplay_Name, x, y, Sorted_Score[i].second, sf::Color::Yellow, 60);
		Text_Style(Desplay_Score, x + 400, y, convert, sf::Color::Green, 45);

		wind.draw(Desplay_Name);
		wind.draw(Desplay_Score);
	}
}






