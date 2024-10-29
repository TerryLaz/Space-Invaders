#include "Game.h"

void Game::initiateText()
{
	this->font.loadFromFile("C:/windows/fonts/arial.ttf");
	this->text.setFont(this->font);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::Green);
	this->text.setPosition(0.0f, 0.0f);
	this->text.setString("Lives: " + to_string(this->theShip->getLife())
		+ "  Score: " + to_string(this->scorePtr->getScore())
		+ "   Time: " + to_string((int)this->totalTime.asSeconds()));
}

Game::Game()
	:GameState("Game"),
	timePerFrame(sf::seconds(1.0f / 60.0f)),
	elapsedTimeSinceLastUpdate(sf::Time::Zero),
	totalTime(sf::Time::Zero),
	gamePaused(false)
{
	srand((unsigned)time(0));

	music.openFromFile("../Audio/music.wav");
	music.setVolume(5);
	music.play();
	music.setLoop(true);

	pauseText.setFont(this->font);
	pauseText.setCharacterSize(50);
	pauseText.setFillColor(sf::Color::Red);
	pauseText.setPosition(WIDTH / 2 - 100, HEIGHT / 2);
	pauseText.setString("PAUSED");

	scorePtr = new Score();
	theShip = new Ship();
	projectilePtr = new Projectile();
	theShip->receiveProjectile(this->projectilePtr);
	motherShip = new MotherShip(WIDTH / 2, 20);
	float offsetX = 0;
	float offsetY = 0;
	for (int i = 0; i < CAP; i++)
	{
		aliens[i] = new Alien(offsetX, offsetY);
		alienProjectiles[i] = new Projectile(5.0f);
		aliens[i]->receiveProjectile(this->alienProjectiles[i]);
		offsetX += 100.0f;
		if (i == 4)
		{
			offsetX = 0;
			offsetY = 100;
		}
	}
	initiateText();
}

Game::~Game()
{
	delete this->scorePtr;
	delete this->theShip;
	delete this->projectilePtr;
	for (int i = 0; i < CAP; i++)
	{
		delete aliens[i];
		delete alienProjectiles[i];
	}
	delete this->motherShip;
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (!gamePaused)
				{
					theShip->shoot();
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				if (!gamePaused)
				{
					this->music.pause();
					gamePaused = true;
				}
				else if(gamePaused)
				{
					this->music.play();
					gamePaused = false;
				}
			}
		}
	}
}

State Game::update()
{
	State currentState = State::NO_CHANGE;
	elapsedTimeSinceLastUpdate += clock.restart();
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;
		if (!gamePaused)
		{
			totalTime += timePerFrame;
			//Ship movement
			theShip->move(0, WIDTH);
			//Projectile movement
			if (projectilePtr->insideWindow() &&
				projectilePtr->isMoving())
			{
				projectilePtr->move(projectilePtr->getSpeed());
			}
			else if (!projectilePtr->insideWindow())
			{
				projectilePtr->stopMoving();
				theShip->receiveProjectile(projectilePtr);
			}
			//Alien/projectile movement
			for (int i = 0; i < CAP; i++)
			{
				aliens[i]->move(0, WIDTH);
				if (Alien::allDown)
				{
					for (int i = 0; i < CAP; i++)
					{
						aliens[i]->moveDown();
					}
				}
				if (alienProjectiles[i]->insideWindowDown() &&
					alienProjectiles[i]->isMoving())
				{
					alienProjectiles[i]->move(alienProjectiles[i]->getSpeed());
				}
				else if (!alienProjectiles[i]->insideWindowDown())
				{
					alienProjectiles[i]->stopMoving();
					aliens[i]->receiveProjectile(alienProjectiles[i]);
				}
			}
			//MotherShip movement
			if (motherShip->isAlive())
			{
				motherShip->move(0, WIDTH);
			}
			if (motherShip->isAlive() && !motherShip->isPlaying())
			{
				motherShip->playSound();
			}
			//Collision check
			for (int i = 0; i < CAP; i++)
			{
				if (aliens[i]->isAlive())
				{
					if (projectilePtr->hitBy(*aliens[i]))
					{
						projectilePtr->stopMoving();
						theShip->receiveProjectile(projectilePtr);
						aliens[i]->die();
						scorePtr->increaseScore(1);
					}
					if (alienProjectiles[i]->hitBy(*theShip))
					{
						alienProjectiles[i]->stopMoving();
						aliens[i]->receiveProjectile(alienProjectiles[i]);
						theShip->decreaseLife();
					}
					if (theShip->invaded(aliens[i]))
					{
						scorePtr->setFinalScore(scorePtr->getScore(), theShip->getLife(), (int)totalTime.asSeconds());
						scorePtr->write(to_string(scorePtr->getFinalScore()));
						currentState = State::HIGHSCORE_INPUT;
					}
				}
			}
			if (motherShip->isAlive())
			{
				if (projectilePtr->hitBy(*motherShip))
				{
					scorePtr->increaseScore(10);
					scorePtr->setFinalScore(scorePtr->getScore(), theShip->getLife(), (int)totalTime.asSeconds());
					scorePtr->write(to_string(scorePtr->getFinalScore()));
					currentState = State::HIGHSCORE_INPUT;
				}
				else if (theShip->invaded(motherShip))
				{
					scorePtr->setFinalScore(scorePtr->getScore(), theShip->getLife(), (int)totalTime.asSeconds());
					scorePtr->write(to_string(scorePtr->getFinalScore()));
					currentState = State::HIGHSCORE_INPUT;
				}
			}
			//Alien Shoot
			int r = rand() % CAP;
			int chance = rand() % 5 + 1;
			if (chance == 5)
			{
				aliens[r]->shoot();
			}
			//Spawn MotherShip
			if (scorePtr->getScore() >= CAP)
			{
				motherShip->spawn();
			}
			//GAME OVER
			if (theShip->getLife() <= 0 || scorePtr->getScore() >= CAP + 1)
			{
				scorePtr->setFinalScore(scorePtr->getScore(), theShip->getLife(), (int)totalTime.asSeconds());
				scorePtr->write(to_string(scorePtr->getFinalScore()));
				currentState = State::HIGHSCORE_INPUT;
			}
			//Update text
			this->text.setString("Lives: " + to_string(theShip->getLife())
				+ "  Score: " + to_string(scorePtr->getScore())
				+ "  Time: " + to_string((int)totalTime.asSeconds()));
			//Escape
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				currentState = State::MENU;
			}
		}
	}
	return currentState;
}

void Game::render()
{
	window.clear();
	window.draw(*theShip);
	window.draw(*projectilePtr);
	window.draw(text);
	if (motherShip->isAlive())
	{
		window.draw(*motherShip);
	}
	for (int i = 0; i < CAP; i++)
	{
		
		if (aliens[i]->isAlive())
		{
			window.draw(*aliens[i]);
			window.draw(*alienProjectiles[i]);
		}
	}
	if (gamePaused)
	{
		window.clear();
		window.draw(pauseText);
	}
	window.display();
}
