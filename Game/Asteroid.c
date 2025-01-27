#include "Asteroid.h"

AsteroidManager asteroidManager;

void LoadTexture(void);
void AsteroidCreate(void);
void WaveCreate(void);

void LoadAsteroid(void)
{
	LoadTexture();
	asteroidManager.currentWave = 1;
	asteroidManager.asteroidsNumb = 0;
	WaveCreate();
}

void UpdateAsteroid(float _dt)
{
}

void DrawAsteroid(sfRenderWindow* const _renderWindow)
{
	for (int i = 0; i < asteroidManager.asteroidsNumb; i++)
	{
		DrawWraparound(_renderWindow, asteroidManager.asteroids[i].sprite);
		//sfRenderWindow_drawSprite(_renderWindow, asteroidManager.asteroids[i].sprite, NULL);
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

	asteroidManager.textureMedium = sfTexture_createFromFile("Assets/Sprites/Background/Meteor2.png", NULL);
	if (!asteroidManager.textureMedium)
	{
		printf("Error loading asteroid medium texture\n");
		return;
	}

	asteroidManager.textureSmall = sfTexture_createFromFile("Assets/Sprites/Background/Meteor1.png", NULL);
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
	sfSprite_setOrigin(asteroid->sprite, (sfVector2f) { textureSize.x / 2, textureSize.x / 2 });
	sfSprite_setPosition(asteroid->sprite, (sfVector2f) { (float)(rand() % SCREEN_WIDTH), (float)(rand() % SCREEN_HEIGHT) });
	sfSprite_setRotation(asteroid->sprite, (float)(rand() % 360));
	asteroid->size = LARGE;
	asteroid->velocity = (sfVector2f) { (float)(rand() % 200 - 100), (float)(rand() % 200 - 100) };
	asteroidManager.asteroidsNumb++;
}

void WaveCreate(void)
{
	int asteroidNumb = asteroidManager.currentWave + 3;
	for (int i = 0; i < asteroidNumb; i++)
	{
		AsteroidCreate();
	}
}

void AsteroidHit()
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