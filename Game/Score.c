#include "Score.h"

Score scores = { 0 };

void LoadScore(void)
{
	scores.score = 0;
	scores.scoreLife = 0;
	scores.highScore = 0;
}

void AddScore(unsigned int _value)
{
	scores.score += _value;
	scores.scoreLife += _value;
	scores.highScore = scores.score > scores.highScore ? scores.score : scores.highScore;
}

void CleanupScore(void)
{
	scores.score = 0;
}

unsigned int GetScore(void)
{
	return scores.score;
}

unsigned int GetHighScore(void)
{
	return scores.highScore;
}

unsigned int GetScoreLife(void)
{
	return scores.scoreLife;
}

void RemovetScoreLife(void)
{
	scores.scoreLife -= 5000;
}