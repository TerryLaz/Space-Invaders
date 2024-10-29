#include "Score.h"

Score::Score()
	:score(0),
	finalScore(0)
{
}

Score::~Score()
{
}

void Score::write(string aScore)
{
	ofstream writeFile;
	writeFile.open("../Datafiles/HighScore.txt");
	if (writeFile.is_open())
	{
		writeFile << aScore;
		writeFile.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

void Score::increaseScore(int score)
{
	this->score += score;
}

void Score::setFinalScore(int score, int lives, int time)
{
	this->finalScore = score * (lives + 1) * (100 - time);
}

int Score::getFinalScore() const
{
	return this->finalScore;
}

int Score::getScore() const
{
	return this->score;
}
