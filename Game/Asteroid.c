#include "Asteroid.h"

AsteroidManager asteroidManager;

void LoadTexture(void);
void AsteroidCreate(void);
void WaveCreate(void);
void UpdateAsteroidPosition(float _dt, Asteroid* _asteroid);

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
	}
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
}

void LoadTexture(void)
{
	asteroidManager.textureLarge = sfTexture_createFromFile("Assets/Sprites/Background/Meteor3.png", NULL);
	if (!asteroidManager.textureLarge)
	{
		printf("Error loading asteroid large texture\n");
		return;
	}

	asteroidManager.textureMedium = sfTexture_createFromFile("Assets/Sprites/Background/Meteor4.png", NULL);
	if (!asteroidManager.textureMedium)
	{
		printf("Error loading asteroid medium texture\n");
		return;
	}

	asteroidManager.textureSmall = sfTexture_createFromFile("Assets/Sprites/Background/Meteor5.png", NULL);
	if (!asteroidManager.textureSmall)
	{
		printf("Error loading asteroid small texture\n");
		return;
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
	asteroid->velocity = (sfVector2f) { (float)(rand() % 300 - 150), (float)(rand() % 300 - 150) };
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

void UpdateAsteroidPosition(float _dt, Asteroid* _asteroid)
{
	sfSprite_move(_asteroid->sprite, (sfVector2f){ _asteroid->velocity.x * _dt,_asteroid->velocity.y * _dt});

	sfVector2f asteroidPosition = sfSprite_getPosition(_asteroid->sprite);
	if (asteroidPosition.x < 0)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f){ SCREEN_WIDTH, asteroidPosition.y });
	}
	else if (asteroidPosition.x > SCREEN_WIDTH)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f){ 0, asteroidPosition.y });
	}
	if (asteroidPosition.y < 0)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f){ asteroidPosition.x, SCREEN_HEIGHT });
	}
	else if (asteroidPosition.y > SCREEN_HEIGHT)
	{
		sfSprite_setPosition(_asteroid->sprite, (sfVector2f){ asteroidPosition.x, 0 });
	}
}

void AsteroidHit(Asteroid* _asteroid)
{
}

void SortAsteroideList(unsigned int _index)
{
	for (unsigned int i = _index; i < asteroidManager.asteroidsNumb - 1; i++)
	{
		asteroidManager.asteroids[i] = asteroidManager.asteroids[i + 1];
	}
	asteroidManager.asteroidsNumb--;
}