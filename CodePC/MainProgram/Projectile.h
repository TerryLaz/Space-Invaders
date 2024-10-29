#pragma once
#include "Entity.h"

class Projectile : public sf::Drawable
{
private:
	sf::RectangleShape rectShape;
	bool moves;
	float speed;
public:
	Projectile();
	Projectile(float speed);
	~Projectile();

	void go();
	bool isMoving();
	bool insideWindow();
	bool insideWindowDown();
	void stopMoving();
	void setPosition(float x, float y);
	void move(float speed);
	float getSpeed()const;
	sf::FloatRect getGlobalBounds()const;
	bool hitBy(const Entity& aEntity)const;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};