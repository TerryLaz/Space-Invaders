#pragma once
#include "Entity.h"
#include "Projectile.h"

class Ship : public Entity
{
private:
	sf::Music shootSound;
	Projectile *aProjectile;
	int life;
	
	void releaseProjectile();
public:
	Ship();
	virtual ~Ship();

	void receiveProjectile(Projectile* projectilePtr);
	bool invaded(Entity* aEntity);
	void decreaseLife();
	int getLife()const;

	virtual void shoot() override;
	virtual void move(float leftBounds, float rightBounds) override;
};