#ifndef GAME_H
#define GAME_H

#include "Common.h"

typedef struct Game
{
	float score;
}Game;

void LoadGame(void);
void UpdateGame(float, sfRenderWindow*);
void OnKeyPressedGame(sfKeyEvent, sfRenderWindow*);
void OnMousePressedGame(sfMouseButtonEvent, sfRenderWindow*);
void DrawGame(sfRenderWindow*);
void CleanupGame();
#endif

