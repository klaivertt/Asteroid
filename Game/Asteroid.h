#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "Wraparound.h"

#define ASTEROID_MAX 1000

enum AsteroidSize
{
	LARGE,
	MEDIUM,
	SMALL
};

typedef struct Asteroid
{
	sfSprite* sprite;
	sfVector2f velocity;
	enum AsteroidSize size;
}Asteroid;

typedef struct AsteroidManager
{
	Asteroid asteroids[ASTEROID_MAX];
	unsigned int asteroidsNumb;
	sfTexture* textureLarge;
	sfTexture* textureMedium;
	sfTexture* textureSmall;
	unsigned int currentWave;
}AsteroidManager;

void LoadAsteroid(void);	
void UpdateAsteroid(float _dt);
void DrawAsteroid(sfRenderWindow* const _renderWindow);
void CleanupAsteroid(void);

#endif // !ASTEROID_H