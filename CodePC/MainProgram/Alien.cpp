#include "Alien.h"
bool Alien::allDown = false;

void Alien::releaseProjectile()
{
	this->alienProjectile->go();
	this->alienProjectile = nullptr;
}

Alien::Alien(float x, float y)
	:Entity("../Images/AlienSpriteSheet.png", 3),
	direction(RIGHT),
	alive(true)
{
	this->setTextureRect();
	this->setSpritePosition(x, y + 20);
	this->setSpriteScale(0.45, 0.45);
}

Alien::~Alien()
{
}

void Alien::receiveProjectile(Projectile * projectilePtr)
{
	this->alienProjectile = projectilePtr;
	this->alienProjectile->setPosition(this->getGlobalBounds().left, this->getGlobalBounds().top);
}

void Alien::changeDir()
{
	this->direction *= -1;
}

void Alien::die()
{
	this->alive = false;
}

void Alien::moveDown()
{
	if (this->alive)
	{
		this->setSpritePosition(this->getGlobalBounds().left, this->getGlobalBounds().top + 50);
		this->changeDir();
		allDown = false;
	}
}

bool Alien::isAlive() const
{
	return this->alive;
}

void Alien::shoot()
{
	if (this->alienProjectile != nullptr)
	{
		this->releaseProjectile();
	}
}

void Alien::move(float leftBounds, float rightBounds)
{
	if (this->alive)
	{
		this->moveSprite(this->getSpeed()*this->direction, 0);
		if (this->alienProjectile != nullptr && !this->alienProjectile->isMoving())
		{
			this->alienProjectile->setPosition(this->getGlobalBounds().left, this->getGlobalBounds().top);
		}
		if (this->getGlobalBounds().left + this->getGlobalBounds().width >= rightBounds)
		{
			allDown = true;
		}
		if (this->getGlobalBounds().left <= leftBounds)
		{
			allDown = true;
		}
		this->animate();
	}
}
