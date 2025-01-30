#ifndef ASTEROID_H
#define ASTEROID_H

#include "Common.h"
#include "Wraparound.h"
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
	sfSoundBuffer* asteroidExplosionBuffer;
	sfSound* asteroidExplosionSound;
}AsteroidManager;

//* @brief Load the asteroid textures and sounds
void LoadAsteroid(void);	

//* @brief Update the asteroid
//* @param _dt Delta time
void UpdateAsteroid(float _dt);

//* @brief Draw the asteroid
//* @param _renderWindow The window to draw the asteroid
void DrawAsteroid(sfRenderWindow* const _renderWindow);

//* @brief Cleanup the asteroid
void CleanupAsteroid(void);

//* @brief Get the asteroids table
//* @return The asteroids table
Asteroid* GetAsteroids(void);

//* @brief Get the number of asteroids
//* @return The number of asteroids
int GetAsteroidNumb(void);

//* @brief Destroy an asteroid
//* @param _index The index of the asteroid
void DestroyAsteroid(unsigned int _index);

//* @brief Set player pos
//* @param _position The position of the player
void SetPlayerPosition(sfVector2f _position);

#endif // !ASTEROID_H