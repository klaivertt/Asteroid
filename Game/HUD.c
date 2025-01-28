#include "HUD.h"

HUDData hudData;

void LoadHud(void)
{
	hudData.textScore = InitText("Score: 0", 42, (sfVector2f) { 50, 50 });
	if (!hudData.textScore)
	{
		printf("Error: Could not load text\n");
		exit(EXIT_FAILURE);
	}

	hudData.emptylLifeTexture = sfTexture_createFromFile("Assets/Sprites/HUD/EmptylLife.png", NULL);
	if (!hudData.emptylLifeTexture)
	{
		printf("Error: Could not load empty life texture\n");
		exit(EXIT_FAILURE);
	}

	hudData.fullLifeTexture = sfTexture_createFromFile("Assets/Sprites/HUD/FullLife.png", NULL);
	if (!hudData.fullLifeTexture)
	{
		printf("Error: Could not load full life texture\n");
		exit(EXIT_FAILURE);
	}

	sfVector2f startPosition = { (SCREEN_WIDTH - (PLAYER_MAX_HEALTH * 50)) / 2, 50 };
	for (int i = 0; i < PLAYER_MAX_HEALTH; i++)
	{
		hudData.healthBar[i] = sfSprite_create();
		if (i < GetPlayerHealth())
		{
			sfSprite_setTexture(hudData.healthBar[i], hudData.fullLifeTexture, sfTrue);
		}
		else
		{
			sfSprite_setTexture(hudData.healthBar[i], hudData.emptylLifeTexture, sfTrue);
		}

		sfSprite_setPosition(hudData.healthBar[i], (sfVector2f) { startPosition.x + (i * 50), startPosition.y });
	}
}

void UpdateHud(float _dt)
{
	UpdateText(&hudData.textScore, "Score: %d", GetScore());
	for (int i = 0; i < PLAYER_MAX_HEALTH; i++)
	{
		if (i < GetPlayerHealth())
		{
			sfSprite_setTexture(hudData.healthBar[i], hudData.fullLifeTexture, sfTrue);
		}
		else
		{
			sfSprite_setTexture(hudData.healthBar[i], hudData.emptylLifeTexture, sfTrue);
		}
	}
}

void DrawHud(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawText(_renderWindow, hudData.textScore, NULL);
	for (int i = 0; i < PLAYER_MAX_HEALTH; i++)
	{
		sfRenderWindow_drawSprite(_renderWindow, hudData.healthBar[i], NULL);
	}
}

void CleanupHud(void)
{
}
