#pragma once
#include "Entity.h"

class MotherShip : public Entity
{
private:
	int direction;
	bool alive;
	bool playingSound;
	sf::Music msSound;
public:
	MotherShip(float x, float y);
	virtual ~MotherShip();

	void changeDir();
	void die();
	void spawn();
	void playSound();
	bool isPlaying()const;
	bool isAlive()const;

	virtual void shoot() override;
	virtual void move(float leftBounds, float rightBounds) override;
};