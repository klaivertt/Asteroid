#include "Game.h"

sfSprite* backgroundSprite;
sfTexture* backgroundTexture;
void LoadGame(void)
{
	backgroundSprite = sfSprite_create();
	if (!backgroundSprite)
	{
		printf("Error creating background sprite\n");
		return;
	}
	backgroundTexture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!backgroundTexture)
	{
		printf("Error loading background texture\n");
		sfSprite_destroy(backgroundSprite);
		backgroundSprite = NULL;
		return;
	}
	sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
	sfSprite_setScale(backgroundSprite, (sfVector2f) { 2, 2 });

	LoadPlayer();
	LoadBullet();
	LoadHud();
}

void KeyPressedGame(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
		break;
	case sfKeySpace:
		break;
	default:
		break;
	}
}

void UpdateGame(sfRenderWindow* const _renderWindow, float _dt)
{
	UpdatePlayer(_dt);
	UpdateBullet(_dt);
}

void DrawGame(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, backgroundSprite, NULL);
	DrawBullet(_renderWindow);
	DrawPlayer(_renderWindow);
	DrawHud(_renderWindow);
}

void CleanupGame(void)
{
	CleanupPlayer();
	CleanupBullet();
	sfSprite_destroy(backgroundSprite);
	backgroundSprite = NULL;
}
