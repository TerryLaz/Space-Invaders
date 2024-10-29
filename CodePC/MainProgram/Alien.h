#pragma once
#include "Entity.h"
#include "Projectile.h"

class Alien : public Entity
{
public:
	static bool allDown;
private:
	Projectile *alienProjectile;
	int direction;
	bool alive;

	void releaseProjectile();
public:
	Alien(float x, float y);
	virtual ~Alien();
	
	void receiveProjectile(Projectile* projectilePtr);
	void changeDir();
	void die();
	void moveDown();
	bool isAlive()const;
	
	virtual void shoot() override;
	virtual void move(float leftBounds, float rightBounds) override;
};