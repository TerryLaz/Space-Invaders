#include "Projectile.h"

Projectile::Projectile()
	:rectShape(sf::Vector2f(2,15)),
	moves(false),
	speed(-5.0f)
{
	this->rectShape.setFillColor(sf::Color::White);
}

Projectile::Projectile(float speed)
	:rectShape(sf::Vector2f(2,15)),
	moves(false),
	speed(speed)
{
	this->rectShape.setFillColor(sf::Color::Yellow);
}

Projectile::~Projectile()
{
}

void Projectile::go()
{
	this->moves = true;
}

bool Projectile::isMoving()
{
	return moves;
}

bool Projectile::insideWindow()
{
	return this->rectShape.getGlobalBounds().top + this->rectShape.getGlobalBounds().height > 0;
}

bool Projectile::insideWindowDown()
{
	return this->rectShape.getGlobalBounds().top < 600;
}

void Projectile::stopMoving()
{
	this->moves = false;
}

void Projectile::setPosition(float x, float y)
{
	this->rectShape.setPosition(x, y);
}

void Projectile::move(float speed)
{
	this->rectShape.move(0, speed);
}

float Projectile::getSpeed() const
{
	return this->speed;
}

sf::FloatRect Projectile::getGlobalBounds() const
{
	return this->rectShape.getGlobalBounds();
}

bool Projectile::hitBy(const Entity & aEntity) const
{
	return this->getGlobalBounds().intersects(aEntity.getGlobalBounds());
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->rectShape);
}
