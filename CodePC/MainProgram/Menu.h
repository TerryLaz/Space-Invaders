#pragma once
#include"GameState.h"

class Menu :public GameState
{
private:
	sf::Text alternatives[2];
	sf::Font font;
	sf::Texture texture;
	sf::Sprite sprite;
	int selected;
	bool done;

	void moveUp();
	void moveDown();
public:
	Menu();
	virtual ~Menu();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;
};