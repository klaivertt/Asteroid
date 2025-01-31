#include "HUD.h"

HUDData hudData;

void LoadHud(void)
{
	hudData.textScore = InitText("Score: 0", 42, (sfVector2f) { 40, 20 });
	if (!hudData.textScore)
	{
		//printf("Error: Could not load text\n");
		exit(EXIT_FAILURE);
	}


	if (GetHollowPurpleIsActivated())
	{
		sfText_setColor(hudData.textScore, sfColor_fromRGB(160, 10, 220));
	}

	hudData.emptylLifeTexture = sfTexture_createFromFile("Assets/Sprites/HUD/EmptylLife.png", NULL);
	if (!hudData.emptylLifeTexture)
	{
		//printf("Error: Could not load empty life texture\n");
		exit(EXIT_FAILURE);
	}

	if (GetHollowPurpleIsActivated())
	{
		hudData.fullLifeTexture = sfTexture_createFromFile("Assets/Sprites/HUD/PurpleFullLife.png", NULL);
		if (!hudData.fullLifeTexture)
		{
			//printf("Error: Could not load full life texture\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		hudData.fullLifeTexture = sfTexture_createFromFile("Assets/Sprites/HUD/FullLife.png", NULL);
		if (!hudData.fullLifeTexture)
		{
			//printf("Error: Could not load full life texture\n");
			exit(EXIT_FAILURE);
		}
	}

	sfVector2f startPosition = { (SCREEN_WIDTH - (PLAYER_MAX_HEALTH * 75)) / 2, 30 };
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

		sfSprite_setPosition(hudData.healthBar[i], (sfVector2f) { startPosition.x + (i * 75), startPosition.y });
	}

	hudData.purpleTexture = sfTexture_createFromFile("Assets/Sprites/Item/PurplePower.png", NULL);
	hudData.purplePower = sfSprite_create();
	sfSprite_setTexture(hudData.purplePower, hudData.purpleTexture, sfTrue);
	sfSprite_setPosition(hudData.purplePower, (sfVector2f) { SCREEN_WIDTH - 50, 50 });
	sfFloatRect purpleBound = sfSprite_getGlobalBounds(hudData.purplePower);
	sfSprite_setOrigin(hudData.purplePower, (sfVector2f) { purpleBound.width / 2, purpleBound.height / 2 });

	hudData.barTexture = sfTexture_createFromFile("Assets/Sprites/Hud/EnergieBar2.png", NULL);
	hudData.bar = sfSprite_create();
	sfSprite_setTexture(hudData.bar, hudData.barTexture, sfTrue);
	sfSprite_setPosition(hudData.bar, (sfVector2f) { SCREEN_WIDTH - 50, 75 });
	sfFloatRect barBound = sfSprite_getGlobalBounds(hudData.bar);
	sfSprite_setOrigin(hudData.bar, (sfVector2f) { 0, barBound.height / 2 });
	sfSprite_setRotation(hudData.bar, 90);	
	
	hudData.barFullTexture = sfTexture_createFromFile("Assets/Sprites/Hud/EnergieBarColor2.png", NULL);
	hudData.barFull = sfSprite_create();
	sfSprite_setTexture(hudData.barFull, hudData.barFullTexture, sfTrue);
	sfSprite_setPosition(hudData.barFull, (sfVector2f) { SCREEN_WIDTH - 50, 93 });
	sfFloatRect barFullBound = sfSprite_getGlobalBounds(hudData.barFull);
	sfSprite_setOrigin(hudData.barFull, (sfVector2f) { 0, barFullBound.height / 2 });
	sfSprite_setRotation(hudData.barFull, 90);
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

	sfIntRect area = sfSprite_getTextureRect(hudData.barFull);
	sfVector2u size = sfTexture_getSize(sfSprite_getTexture(hudData.barFull));
	area.width = size.x * GetPurple() / PURPLE_MAX;
	sfSprite_setTextureRect(hudData.barFull, area);
}

void DrawHud(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawText(_renderWindow, hudData.textScore, NULL);
	for (int i = 0; i < PLAYER_MAX_HEALTH; i++)
	{
		sfRenderWindow_drawSprite(_renderWindow, hudData.healthBar[i], NULL);
	}
	sfRenderWindow_drawSprite(_renderWindow, hudData.purplePower, NULL);
	sfRenderWindow_drawSprite(_renderWindow, hudData.bar, NULL);
	sfRenderWindow_drawSprite(_renderWindow, hudData.barFull, NULL);
}

void CleanupHud(void)
{
}
