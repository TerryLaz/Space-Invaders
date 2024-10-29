#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class GameState
{
public:
	static const int HEIGHT = 600;
	static const int WIDTH = 900;
protected:
	sf::RenderWindow window;
public:
	GameState(string title);
	virtual ~GameState();
	virtual State update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
};