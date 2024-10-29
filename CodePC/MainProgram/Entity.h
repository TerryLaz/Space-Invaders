#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>

using namespace std;

class Entity : public sf::Drawable
{
public:
	static const int LEFT = -1;
	static const int RIGHT = 1;
	static const int NO_DIRECTION = 0;
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect intRect;
	float speed;
	int timeCounter;
	int updateTime;
protected:
	void moveSprite(float x, float y);
	void setSpriteScale(float x, float y);
	void setSpritePosition(float x, float y);
	void setSpriteTexture(string fileName);
	void setTextureRect();
	void resetTimeCounter();
	void animate();
	int getTimeCounter()const;
	float getSpeed()const;
public:
	Entity(string fileName, float speed);
	virtual ~Entity();

	sf::FloatRect getGlobalBounds()const;

	virtual void shoot() = 0;
	virtual void move(float leftBounds, float rightBounds) = 0;
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};