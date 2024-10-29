#include "Menu.h"

void Menu::moveUp()
{
	if (selected != 0)
	{
		selected = 0;
		alternatives[0].setFillColor(sf::Color::Red);
		alternatives[1].setFillColor(sf::Color::Yellow);
	}
}

void Menu::moveDown()
{
	if (selected != 1)
	{
		selected = 1;
		alternatives[1].setFillColor(sf::Color::Red);
		alternatives[0].setFillColor(sf::Color::Yellow);
	}
}

Menu::Menu()
	:GameState("Menu")
{
	texture.loadFromFile("../Images/SpaceInvaders.jpg");
	sprite.setTexture(texture);
	sprite.setPosition(WIDTH / 2 - texture.getSize().x / 2, 0);

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Red);
	alternatives[0].setCharacterSize(30);
	alternatives[0].setString("Play");
	alternatives[0].setPosition(WIDTH / 2 - 20, HEIGHT / 2 +100);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::Yellow);
	alternatives[1].setCharacterSize(30);
	alternatives[1].setString("Exit");
	alternatives[1].setPosition(WIDTH / 2 -20, HEIGHT / 2 + 150);

	selected = 0;
	done = false;
}

Menu::~Menu()
{
}

State Menu::update()
{
	State currentState = State::NO_CHANGE;
	if (done)
	{
		if (selected == 0)
		{
			currentState = State::PLAY;
		}
		else if (selected == 1)
		{
			currentState = State::EXIT;
		}
	}

	return currentState;
}

void Menu::render()
{
	window.clear();
	window.draw(sprite);
	for (int i = 0; i < 2; i++)
	{
		
		window.draw(alternatives[i]);
	}
	window.display();
}

void Menu::handleEvents()
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				moveUp();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				moveDown();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				done = true;
			}
		}
	}
}
