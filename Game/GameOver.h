#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Common.h"
#include "GameState.h"
#include "Text.h"
#include "Score.h"
#include "HollowPurple.h"


typedef struct GameOverData
{
	sfTexture* texture;
	sfSprite* sprite;
	sfText* gameOverText;
	sfText* scoreText;
	sfText* highScoreText;
	sfText* pressSpaceText;
	sfText* pressEscapeText;
	sfText* hollowPurple;
}GameOverData;

//* @brief Function to load the Game Over screen resources.
void LoadGameOver(void);

//* @brief Function to handle key pressed events in the Game Over screen.
//* @param _key The key that was pressed.
void KeyPressedGameOver(sfKeyEvent _key);

void UpdateGameOver(sfRenderWindow* const _renderWindow, float _dt);
void DrawGameOver(sfRenderWindow* const _renderWindow);
void CleanupGameOver(void);

#endif // !GAME_OVER_H
