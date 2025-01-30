#include "Menu.h"

MenuData menuData;

void LoadMenu(void)
{
	menuData.texture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!menuData.texture)
	{
		//printf("Error loading menu texture\n");
		return;
	}
	menuData.sprite = sfSprite_create();
	sfSprite_setTexture(menuData.sprite, menuData.texture, sfTrue);
	sfSprite_scale(menuData.sprite, (sfVector2f) { 2, 2 });

	sfVector2u textureSize;
	textureSize = sfTexture_getSize(menuData.texture);	
	menuData.title = InitText(GAME_NAME, 72, (sfVector2f) { (SCREEN_WIDTH / 2), 100 });
	if (!menuData.title)
	{
		//printf("Error loading menu title\n");
		return;
	}
	SetTextOrigin(menuData.title, (sfVector2f) { 2, 2 });

	menuData.play = InitText("Press 'Space' to Play", 38, (sfVector2f) { (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) });
	if (!menuData.play)
	{
		//printf("Error loading menu play text\n");
		return;
	}
	SetTextOrigin(menuData.play, (sfVector2f) { 2, 2 });

	menuData.exit = InitText("Press 'Escape' to Exit", 38, (sfVector2f) { (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 250 });
	if (!menuData.exit)
	{
		//printf("Error loading menu exit text\n");
		return;
	}
	SetTextOrigin(menuData.exit, (sfVector2f) { 2, 2 });
}

void KeyPressedMenu(sfRenderWindow* const _renderWindow, sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		sfRenderWindow_close(_renderWindow);
		break;
	case sfKeySpace:
		SetGameState(GAME);
		break;
	default:
		break;
	}
}

void UpdateMenu(sfRenderWindow* const _renderWindow, float _dt)
{
}

void DrawMenu(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, menuData.sprite, NULL);
	sfRenderWindow_drawText(_renderWindow, menuData.title, NULL);
	sfRenderWindow_drawText(_renderWindow, menuData.play, NULL);
	sfRenderWindow_drawText(_renderWindow, menuData.exit, NULL);
}

void CleanupMenu(void)
{
	sfTexture_destroy(menuData.texture);
	menuData.texture = NULL;

	sfSprite_destroy(menuData.sprite);
	menuData.sprite = NULL;

	CleanupText(&menuData.title);
	CleanupText(&menuData.play);
	CleanupText(&menuData.exit);
}
