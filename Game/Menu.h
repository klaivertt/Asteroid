#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "GameState.h"
#include "Game.h"
#include "Text.h"

typedef struct MenuData
{
	sfTexture* texture;
	sfSprite* sprite;
	sfText* title;
	sfText* play;
	sfText* exit;
}MenuData;

void LoadMenu(void);
void KeyPressedMenu(sfRenderWindow* const _renderWindow, sfKeyEvent _key);
void UpdateMenu(sfRenderWindow* const _renderWindow, float _dt);
void DrawMenu(sfRenderWindow* const _renderWindow);
void CleanupMenu(void);

#endif // !MENU_H
