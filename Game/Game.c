#include "Game.h"

sfSprite* backgroundSprite;
void LoadGame(void)
{
	LoadPlayer();
	LoadBullet();
	backgroundSprite = sfSprite_create();
	if (!backgroundSprite)
	{
		printf("Error creating background sprite\n");
		return EXIT_FAILURE;
	}
	sfTexture* backgroundTexture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!backgroundTexture)
	{
		printf("Error loading background texture\n");
		return EXIT_FAILURE;
	}
	sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
	sfSprite_setScale(backgroundSprite, (sfVector2f) { 2, 2 });
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
	DrawBullet(_renderWindow);
	DrawPlayer(_renderWindow);
	sfRenderWindow_drawSprite(_renderWindow, backgroundSprite, NULL);
}

void CleanupGame(void)
{
	CleanupPlayer();
	CleanupBullet();
	sfSprite_destroy(backgroundSprite);
	backgroundSprite = NULL;
}
