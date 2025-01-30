#include "Game.h"

sfSprite* backgroundSprite;
sfTexture* backgroundTexture;
void CheckBulletAsteroidCollision(void);

void LoadGame(void)
{
	backgroundSprite = sfSprite_create();
	if (!backgroundSprite)
	{
		//printf("Error creating background sprite\n");
		exit(EXIT_FAILURE);
	}
	backgroundTexture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!backgroundTexture)
	{
		//printf("Error loading background texture\n");
		sfSprite_destroy(backgroundSprite);
		backgroundSprite = NULL;
		exit(EXIT_FAILURE);
	}
	sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
	sfSprite_setScale(backgroundSprite, (sfVector2f) { 2, 2 });

	LoadPlayer();
	LoadAsteroid();
	LoadBullet();
	LoadHud();
	LoadScore();
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
	UpdateAsteroid(_dt);
	CheckBulletAsteroidCollision();
	UpdateHud(_dt);

	if (GetPlayerHealth() <= 0)
	{
		SetGameState(GAME_OVER);
	}
}

void DrawGame(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, backgroundSprite, NULL);
	DrawBullet(_renderWindow);
	DrawAsteroid(_renderWindow);
	DrawPlayer(_renderWindow);
	DrawHud(_renderWindow);
}

void CleanupGame(void)
{
	CleanupPlayer();
	CleanupBullet();
	CleanupAsteroid();
	CleanupHud();
	sfSprite_destroy(backgroundSprite);
	backgroundSprite = NULL;
}

void CheckBulletAsteroidCollision(void)
{
	Bullet* bullets = GetBullets();
	unsigned int bulletNumb = GetBulletNumb();

	Asteroid* asteroids = GetAsteroids();
	unsigned int asteroidNum = GetAsteroidNumb();

	if (!bullets || !asteroids)
	{
		//printf("Error: bullets or asteroids array is NULL\n");
		return;
	}

	for (int i = bulletNumb - 1; i >= 0; i--)
	{
		for (int j = asteroidNum - 1; j >= 0; j--)
		{
			sfVector2f bulletPosition = sfSprite_getPosition(bullets[i].sprite);
			sfFloatRect bulletHitbox = sfSprite_getGlobalBounds(bullets[i].sprite);

			if (asteroids[j].sprite)
			{
				sfVector2f asteroidPosition = sfSprite_getPosition(asteroids[j].sprite);
				sfFloatRect asteroidHitbox = sfSprite_getGlobalBounds(asteroids[j].sprite);

				if (ColisionCircleCircle(asteroidPosition, asteroidHitbox.width / 2, bulletPosition, bulletHitbox.width / 2))
				{
					// Handle collision
					DestroyAsteroid(j);
					// Remove bullet
					RemoveBullet(i);
					i--;
					break;
				}
			}
		}
	}
}

