#include "Score.h"

Score scores = { 0 };

void LoadScore(void)
{
	scores.score = 0;
}

void AddScore(unsigned int _value)
{
	scores.score += _value;
}

void CleanupScore(void)
{
	scores.score = 0;
}

unsigned int GetScore(void)
{
	return scores.score;
}