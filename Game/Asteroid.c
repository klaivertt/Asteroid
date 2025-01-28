#include "Asteroid.h"

AsteroidManager asteroidManager;

void LoadTexture(void);
void AsteroidCreate(void);
void WaveCreate(void);
void UpdateWave(void);
void UpdateAsteroidPosition(float _dt, Asteroid* _asteroid);
void CheckBulletAsteroidCollision(unsigned int _index);
void AsteroidPartition(unsigned int _i);
void SortAsteroideList(unsigned int _index);

Asteroid* GetAsteroids(void)
{
	return asteroidManager.asteroids;
}

void LoadAsteroid(void)
{
	LoadTexture();
	asteroidManager.currentWave = 0;
	asteroidManager.asteroidsNumb = 0;
	WaveCreate();
}

void UpdateAsteroid(float _dt)
{
	for (unsigned int i = 0; i < asteroidManager.asteroidsNumb; i++)
	{
		UpdateAsteroidPosition(_dt, &asteroidManager.asteroids[i]);
		CheckBulletAsteroidCollision(i);
	}
	UpdateWave();
}

void DrawAsteroid(sfRenderWindow* const _renderWindow)
{
	for (unsigned int i = 0; i < asteroidManager.asteroidsNumb; i++)
	{
		DrawWraparound(_renderWindow, asteroidManager.asteroids[i].sprite);
	}
}

void CleanupAsteroid(void)
{
	for (unsigned int i = 0; i < asteroidManager.asteroidsNumb; i++)
	{
		if (asteroidManager.asteroids[i].sprite)
		{
			sfSprite_destroy(asteroidManager.asteroids[i].sprite);
		}
	}
	sfTexture_destroy(asteroidManager.textureLarge);
	sfTexture_destroy(asteroidManager.textureMedium);
	sfTexture_destroy(asteroidManager.textureSmall);
}

void LoadTexture(void)
{
	asteroidManager.textureLarge = sfTexture_createFromFile("Assets/Sprites/Background/Meteor3.png", NULL);
	if (!asteroidManager.textureLarge)
	{
		printf("Error loading asteroid large texture\n");
		exit(EXIT_FAILURE);
	}

	asteroidManager.textureMedium = sfTexture_createFromFile("Assets/Sprites/Background/Meteor4.png", NULL);
	if (!asteroidManager.textureMedium)
	{
		printf("Error loading asteroid medium texture\n");
		exit(EXIT_FAILURE);
	}

	asteroidManager.textureSmall = sfTexture_createFromFile("Assets/Sprites/Background/Meteor5.png", NULL);
	if (!asteroidManager.textureSmall)
	{
		printf("Error loading asteroid small texture\n");
		exit(EXIT_FAILURE);
	}
}

void AsteroidCreate(void)
{
	Asteroid* asteroid = &asteroidManager.asteroids[asteroidManager.asteroidsNumb];

	asteroid->sprite = sfSprite_create();
	sfSprite_setTexture(asteroid->sprite, asteroidManager.textureLarge, sfTrue);
	sfVector2u textureSize = sfTexture_getSize(asteroidManager.textureLarge);
	sfSprite_setOrigin(asteroid->sprite, (sfVector2f) { (float)textureSize.x / 2, (float)textureSize.x / 2 });
	sfSprite_setPosition(asteroid->sprite, (sfVector2f) { (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HEIGHT) });
	sfSprite_setRotation(asteroid->sprite, (float)(rand() % 360));
	asteroid->size = LARGE;
	asteroid->velocity = (sfVector2f){ (float)(rand() % 300 - 150), (float)(rand() % 300 - 150) };
	asteroidManager.asteroidsNumb++;
}

void WaveCreate(void)
{
	int asteroidNumb = asteroidManager.currentWave + 3;
	if (asteroidNumb > 50)
	{
		asteroidNumb = 50;
	}
	for (int i = 0; i < asteroidNumb; i++)
	{
		AsteroidCreate();
	}
}

void UpdateWave(void)
{
	if (asteroidManager.asteroidsNumb == 0)
	{
		asteroidManager.currentWave++;
		WaveCreate();
	}
}

void UpdateAsteroidPosition(float _dt, Asteroid* _asteroid)
{
	sfSprite_move(_asteroid->sprite, (sfVector2f) { _asteroid->velocity.x* _dt, _asteroid->velocity.y* _dt });

	sfVector2f asteroidPosition = sfSprite_getPosition(_asteroid->sprite);
	if (asteroidPosition.x < 0)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f) { SCREEN_WIDTH, asteroidPosition.y });
	}
	else if (asteroidPosition.x > SCREEN_WIDTH)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f) { 0, asteroidPosition.y });
	}
	if (asteroidPosition.y < 0)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f) { asteroidPosition.x, SCREEN_HEIGHT });
	}
	else if (asteroidPosition.y > SCREEN_HEIGHT)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f) { asteroidPosition.x, 0 });
	}
}

void CheckBulletAsteroidCollision(unsigned int _index)
{
	Bullet* bullets = GetBullets();
	unsigned int bulletNumb = GetBulletNumb();

	for (unsigned int i = 0; i < bulletNumb; i++)
	{
		if (!asteroidManager.asteroids[_index].sprite || !bullets[i].sprite)
		{
			continue;
		}

		sfFloatRect asteroidHitbox = sfSprite_getGlobalBounds(asteroidManager.asteroids[_index].sprite);
		sfFloatRect bulletHitbox = sfSprite_getGlobalBounds(bullets[i].sprite);

		sfVector2f asteroidPosition = sfSprite_getPosition(asteroidManager.asteroids[_index].sprite);
		sfVector2f bulletPosition = sfSprite_getPosition(bullets[i].sprite);
		if (ColisionCircleCircle(asteroidPosition, asteroidHitbox.width / 2, bulletPosition, bulletHitbox.width / 2))
		{
			// Handle collision
			AsteroidPartition(_index);
			// Remove bullet
			RemoveBullet(i);
			i--;
			break;
		}
	}
}

void AsteroidPartition(unsigned int _i)
{
	Asteroid* asteroid = &asteroidManager.asteroids[_i];
	if (asteroid->size == LARGE)
	{
		// Create 2 medium asteroids
		for (int i = 0; i < 2; i++)
		{
			Asteroid* newAsteroid = &asteroidManager.asteroids[asteroidManager.asteroidsNumb];
			newAsteroid->sprite = sfSprite_create();
			sfSprite_setTexture(newAsteroid->sprite, asteroidManager.textureMedium, sfTrue);
			sfVector2u textureSize = sfTexture_getSize(asteroidManager.textureMedium);
			sfSprite_setOrigin(newAsteroid->sprite, (sfVector2f) { (float)textureSize.x / 2, (float)textureSize.x / 2 });
			sfSprite_setPosition(newAsteroid->sprite, sfSprite_getPosition(asteroid->sprite));
			sfSprite_setRotation(newAsteroid->sprite, (float)(rand() % 360));
			newAsteroid->size = MEDIUM;
			newAsteroid->velocity = (sfVector2f){ (float)(rand() % 400 - 200), (float)(rand() % 400 - 200) };
			asteroidManager.asteroidsNumb++;
		}
		AddScore(20);
		sfSprite_destroy(asteroid->sprite);
		asteroid->sprite = NULL;
		SortAsteroideList(_i);
	}
	else if (asteroid->size == MEDIUM)
	{
		// Create 2 small asteroids
		for (int i = 0; i < 2; i++)
		{
			Asteroid* newAsteroid = &asteroidManager.asteroids[asteroidManager.asteroidsNumb];
			newAsteroid->sprite = sfSprite_create();
			sfSprite_setTexture(newAsteroid->sprite, asteroidManager.textureSmall, sfTrue);
			sfVector2u textureSize = sfTexture_getSize(asteroidManager.textureSmall);
			sfSprite_setOrigin(newAsteroid->sprite, (sfVector2f) { (float)textureSize.x / 2, (float)textureSize.x / 2 });
			sfSprite_setPosition(newAsteroid->sprite, sfSprite_getPosition(asteroid->sprite));
			sfSprite_setRotation(newAsteroid->sprite, (float)(rand() % 360));
			newAsteroid->size = SMALL;
			newAsteroid->velocity = (sfVector2f){ (float)(rand() % 500 - 250), (float)(rand() % 500 - 250) };
			asteroidManager.asteroidsNumb++;
		}

		AddScore(50);
		sfSprite_destroy(asteroid->sprite);
		asteroid->sprite = NULL;
		SortAsteroideList(_i);
	}
	else if (asteroid->size == SMALL)
	{
		// Remove asteroid
		AddScore(100);
		sfSprite_destroy(asteroid->sprite);
		asteroid->sprite = NULL;
		SortAsteroideList(_i);
	}
}

void SortAsteroideList(unsigned int _index)
{
	for (unsigned int i = _index; i < asteroidManager.asteroidsNumb - 1; i++)
	{
		asteroidManager.asteroids[i] = asteroidManager.asteroids[i + 1];
	}
	asteroidManager.asteroidsNumb--;
}