#pragma once
#include "GameState.h"

class HighScoreInput : public GameState
{
private:
	sf::Text labelText;
	sf::Text text;
	sf::Font font;
	std::string name;
	std::string highScore;
	bool done;
public:
	HighScoreInput();
	virtual ~HighScoreInput();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;
};