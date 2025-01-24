#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Common.h"
#include "GameState.h"
#include "Menu.h"
#include "Game.h"

typedef struct GameOverData
{
	sfTexture* texture;
	sfSprite* sprite;
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
