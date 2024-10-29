#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Score
{
private:
	int score;
	int finalScore;
public:
	Score();
	~Score();

	void write(string aScore);
	void increaseScore(int score);
	void setFinalScore(int score, int lives, int time);

	int getFinalScore()const;
	int getScore()const;
};