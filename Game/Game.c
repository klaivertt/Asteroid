#include "Game.h"

GameData gameData = { 0 };

void CheckBulletAsteroidCollision(void);

void LoadGame(void)
{
	gameData.backgroundSprite = sfSprite_create();
	if (!gameData.backgroundSprite)
	{
		//printf("Error creating background sprite\n");
		exit(EXIT_FAILURE);
	}
	gameData.backgroundTexture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!gameData.backgroundTexture)
	{
		//printf("Error loading background texture\n");
		sfSprite_destroy(gameData.backgroundSprite);
		gameData.backgroundSprite = NULL;
		exit(EXIT_FAILURE);
	}
	sfSprite_setTexture(gameData.backgroundSprite, gameData.backgroundTexture, sfTrue);
	sfSprite_setScale(gameData.backgroundSprite, (sfVector2f) { 2, 2 });

	if (GetHollowPurpleIsActivated())
	{
		gameData.music = sfMusic_createFromFile("Assets/Musics/GojoSatoruTheHonoredOne.wav");
		sfMusic_setVolume(gameData.music, 60);
	}
	else
	{
		gameData.music = sfMusic_createFromFile("Assets/Musics/1.ogg");
		sfMusic_setVolume(gameData.music, 50);
	}
	sfMusic_play(gameData.music);
	sfMusic_setLoop(gameData.music, sfTrue);

	LoadPlayer();
	LoadAsteroid();
	LoadBullet();
	LoadScore();
	LoadExplosion();
	LoadHud();
}

void KeyPressedGame(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
	default:
		break;
	}
	KeyPressedPlayer(_key);
}

void UpdateGame(sfRenderWindow* const _renderWindow, float _dt)
{
	UpdatePlayer(_dt);
	UpdateBullet(_dt);
	UpdateAsteroid(_dt);
	CheckBulletAsteroidCollision();
	UpdateExplosion(_dt);
	UpdateHud(_dt);

	if (GetPlayerHealth() <= 0)
	{
		SetGameState(GAME_OVER);
	}
}

void DrawGame(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, gameData.backgroundSprite, NULL);
	DrawBullet(_renderWindow);
	DrawAsteroid(_renderWindow);
	DrawExplosion(_renderWindow);
	DrawPlayer(_renderWindow);
	DrawHud(_renderWindow);
}

void CleanupGame(void)
{
	CleanupPlayer();
	CleanupBullet();
	CleanupAsteroid();
	CleanupHud();
	CleanUpExplosion();
	sfSprite_destroy(gameData.backgroundSprite);
	gameData.backgroundSprite = NULL;
	sfMusic_destroy(gameData.music);
	gameData.music = NULL;
}

void CheckBulletAsteroidCollision(void)
{
	Bullet* bullets = GetBullets();
	unsigned int bulletNumb = GetBulletNumb();

	Asteroid* asteroids = GetAsteroids();
	unsigned int asteroidNum = GetAsteroidNumber();

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
					IncreasePurple();
					break;
				}
			}
		}
	}
}

