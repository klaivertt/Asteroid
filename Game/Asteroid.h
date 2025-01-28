#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "Wraparound.h"
#include "Bullet.h"
#include "Collision.h"
#include "Score.h"

#define ASTEROID_MAX 500

typedef enum AsteroidSize
{
	LARGE,
	MEDIUM,
	SMALL
}AsteroidSize;

typedef struct Asteroid
{
	sfSprite* sprite;
	sfVector2f velocity;
	AsteroidSize size;
	float rotation;
}Asteroid;

typedef struct AsteroidManager
{
	Asteroid asteroids[ASTEROID_MAX];
	unsigned int asteroidsNumb;
	sfTexture* textureLarge;
	sfTexture* textureMedium;
	sfTexture* textureSmall;
	unsigned int currentWave;	
	sfVector2f playerPosition;
}AsteroidManager;

void LoadAsteroid(void);	
void UpdateAsteroid(float _dt);
void DrawAsteroid(sfRenderWindow* const _renderWindow);
void CleanupAsteroid(void);

Asteroid* GetAsteroids(void);
int GetAsteroidNumb(void);
void DestroyAsteroid(unsigned int _index);
void SetPlayerPosition(sfVector2f _position);
#endif // !ASTEROID_H