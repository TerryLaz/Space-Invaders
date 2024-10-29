#pragma once
#include <ctime>
#include "GameState.h"
#include "Ship.h"
#include "Alien.h"
#include "MotherShip.h"
#include "Projectile.h"
#include "Score.h"

class Game : public GameState
{
public:
	static const int CAP = 10;
private:
	sf::Clock clock;
	sf::Time elapsedTimeSinceLastUpdate;
	sf::Time timePerFrame;
	sf::Text text;
	sf::Font font;
	sf::Time totalTime;
	sf::Music music;
	sf::Text pauseText;

	Score *scorePtr;
	Ship *theShip;
	Alien* aliens[CAP];
	MotherShip *motherShip;
	Projectile *projectilePtr;
	Projectile *alienProjectiles[CAP];
	bool gamePaused;

	void initiateText();
public:
	Game();
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;
};