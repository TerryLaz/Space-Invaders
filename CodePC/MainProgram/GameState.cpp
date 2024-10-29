#include "GameState.h"

GameState::GameState(string title)
	:window(sf::VideoMode(WIDTH,HEIGHT), title)
{
}

GameState::~GameState()
{
}
