#ifndef SCORE_H
#define SCORE_H

#include "Common.h"

typedef struct Score
{
	unsigned int score;
	unsigned int scoreLife;
	unsigned int highScore;
}Score;

void LoadScore(void);
void AddScore(unsigned int _value);
void CleanupScore(void);

unsigned int GetScore(void);
unsigned int GetHighScore(void);
unsigned int GetScoreLife(void);
void RemovetScoreLife(void);
#endif // !SCORE_H
