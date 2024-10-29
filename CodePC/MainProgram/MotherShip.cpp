#include "MotherShip.h"

MotherShip::MotherShip(float x, float y)
	:Entity("../Images/MotherShip.png", 10),
	direction(RIGHT),
	alive(false),
	playingSound(false)
{
	this->setSpritePosition(x, y + 20);
	this->setSpriteScale(0.6, 0.6);
	this->msSound.openFromFile("../Audio/motherShip.wav");
	this->msSound.setVolume(8);
	this->msSound.setLoop(true);
}

MotherShip::~MotherShip()
{
}

void MotherShip::changeDir()
{
	this->direction *= -1;
}

void MotherShip::die()
{
	this->alive = false;
}

void MotherShip::spawn()
{
	this->alive = true;
}

void MotherShip::playSound()
{
	this->msSound.play();
	this->playingSound = true;
}

bool MotherShip::isPlaying() const
{
	return this->playingSound;
}

bool MotherShip::isAlive() const
{
	return this->alive;
}

void MotherShip::shoot()
{
}

void MotherShip::move(float leftBounds, float rightBounds)
{
	this->moveSprite(this->getSpeed()*this->direction, 0);
	if (this->getGlobalBounds().left + this->getGlobalBounds().width > rightBounds)
	{
		this->changeDir();
		this->setSpritePosition(rightBounds - this->getGlobalBounds().width, this->getGlobalBounds().top + 50);
	}
	if (this->getGlobalBounds().left < leftBounds)
	{
		this->changeDir();
		this->setSpritePosition(leftBounds, this->getGlobalBounds().top + 50);
	}
}
