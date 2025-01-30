#ifndef SCORE_H
#define SCORE_H

#include "Common.h"

typedef struct Score
{
	unsigned int score;
	unsigned int scoreLife;
	unsigned int highScore;
}Score;

//* @brief Load the score
void LoadScore(void);

//* @brief add value to the score
//* @param _value The value to add
void AddScore(unsigned int _value);

//* @brief Get the score
//* @return The score
unsigned int GetScore(void);

//* @brief Get the high score
//* @return The high score
unsigned int GetHighScore(void);

//* @brief Get the score for life up
//* @return The score for life up
unsigned int GetScoreLife(void);

//* @brief Remove 5000 to the score for life up
void RemovetScoreLife(void);
#endif // !SCORE_H
