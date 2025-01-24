#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "Animations.h"

#define MAX_BUTTONS 5

typedef struct Image
{
	sfTexture* texture;
	sfSprite* sprite;
}Image;

typedef struct Button
{
	Image image;
	sfRectangleShape* rectangle;
	sfText* text;
}Button;

typedef struct Menu
{
	sfFont* font;
	Image background;
	Animation playerIdle;
	Animation* currentAnim;
	Button buttons[MAX_BUTTONS];
	int currentButton;
}Menu;

void LoadMenu(void);
void OnKeyPressedMenu(sfKeyEvent _key, sfRenderWindow* const _render);
void UpdateMenu(float);
void DrawMenu(sfRenderWindow*);
void CleanMenu(void);
void CleanupMenu();
#endif