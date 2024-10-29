#include "Entity.h"

Entity::Entity(string fileName, float speed)
	:speed(speed),timeCounter(0),updateTime(30)
{
	this->texture.loadFromFile(fileName);
	this->sprite.setTexture(this->texture);
}

Entity::~Entity()
{
}

void Entity::moveSprite(float x, float y)
{
	this->sprite.move(x, y);
}

void Entity::setSpritePosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::setSpriteTexture(string fileName)
{
	this->texture.loadFromFile(fileName);
	this->sprite.setTexture(this->texture);
}

void Entity::setTextureRect()
{
	this->intRect = sf::IntRect(0, 0, this->texture.getSize().x / 2, this->texture.getSize().y);
	this->sprite.setTextureRect(this->intRect);
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Entity::resetTimeCounter()
{
	this->timeCounter = 0;
}

int Entity::getTimeCounter() const
{
	return this->timeCounter;
}

void Entity::animate()
{
	this->timeCounter = (this->timeCounter + 1) % this->updateTime;
	if (this->timeCounter == 0)
	{
		this->intRect.left = (this->intRect.left + this->intRect.width) % this->texture.getSize().x;
	}
	this->sprite.setTextureRect(this->intRect);
}

void Entity::setSpriteScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

float Entity::getSpeed() const
{
	return this->speed;
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
