#ifndef SCORE_H
#define SCORE_H

#include "Common.h"

typedef struct Score
{
	unsigned int score;
}Score;

void LoadScore(void);
void AddScore(unsigned int _value);
void CleanupScore(void);

unsigned int GetScore(void);

#endif // !SCORE_H
