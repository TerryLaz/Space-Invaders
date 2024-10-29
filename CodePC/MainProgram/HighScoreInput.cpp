#include "HighScoreInput.h"

HighScoreInput::HighScoreInput()
	:GameState("HighScore")
{
	ifstream readFile;
	readFile.open("../Datafiles/HighScore.txt");
	if (readFile.is_open())
	{
		readFile >> highScore;
		readFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	labelText.setFont(font);
	labelText.setPosition(50.f, 50.f);
	labelText.setFillColor(sf::Color::Green);
	labelText.setCharacterSize(30);
	labelText.setString("Score: " + highScore + "\nInput name (<enter> when done)");

	text.setFont(font);
	text.setPosition(200.f, 200.f);
	text.setFillColor(sf::Color::Green);
	text.setCharacterSize(30);
	name = "";
	text.setString(name);

	done = false;
}

HighScoreInput::~HighScoreInput()
{
}

State HighScoreInput::update()
{
	State currentState = State::NO_CHANGE;
	if (done)
	{
		currentState = State::MENU;
	}
	return currentState;
}

void HighScoreInput::render()
{
	window.clear();
	window.draw(labelText);
	window.draw(text);
	window.display();
}

void HighScoreInput::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.text.unicode >= 0 && event.text.unicode <= 25)
			{
				name += (char)(event.text.unicode + 65);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				name.erase(name.length() - 1, 1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				done = true;
			}
		}
		text.setString(name);
	}
}
