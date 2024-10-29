#include "Ship.h"

void Ship::releaseProjectile()
{
	this->aProjectile->go();
	this->aProjectile = nullptr;
}

Ship::Ship()
	:Entity("../Images/Ship.png", 5),
	life(3)
{
	this->setSpritePosition(450, 552);
	this->setSpriteScale(0.15, 0.15);
}

Ship::~Ship()
{
}

void Ship::receiveProjectile(Projectile * projectilePtr)
{
	this->aProjectile = projectilePtr;
	this->aProjectile->setPosition(this->getGlobalBounds().left + this->getGlobalBounds().width / 2, this->getGlobalBounds().top);
}

bool Ship::invaded(Entity* aEntity)
{
	return this->getGlobalBounds().intersects(aEntity->getGlobalBounds());
}

void Ship::decreaseLife()
{
	this->life--;
}

int Ship::getLife()const
{
	return this->life;
}

void Ship::shoot()
{
	if (this->aProjectile != nullptr)
	{
		this->releaseProjectile();
		this->shootSound.openFromFile("../Audio/shoot.wav");
		this->shootSound.setVolume(10);
		this->shootSound.play();
		this->shootSound.setLoop(false);	
	}
}

void Ship::move(float leftBounds, float rightBounds)
{
	if (this->aProjectile != nullptr && !this->aProjectile->isMoving())
	{
		this->aProjectile->setPosition(this->getGlobalBounds().left + this->getGlobalBounds().width / 2, this->getGlobalBounds().top);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->moveSprite(this->getSpeed(), 0);
		if (this->getGlobalBounds().left + this->getGlobalBounds().width > rightBounds)
		{
			this->setSpritePosition(rightBounds - this->getGlobalBounds().width, 538);
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->moveSprite(-(this->getSpeed()), 0);
		if (this->getGlobalBounds().left < leftBounds)
		{
			this->setSpritePosition(leftBounds, 538);
		}
	}
}
