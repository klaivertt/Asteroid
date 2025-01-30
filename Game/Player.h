#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"
#include "Wraparound.h"
#include "Score.h"
#include "Collision.h"
#include "Asteroid.h"

#define PLAYER_BASE_SPEED 5.f
#define MAX_ACCELERATE_FORCE 50
#define FIRE_RATE 0.1f
#define PLAYER_HEALTH 3
#define PLAYER_MAX_HEALTH 9

#define SHIELD_TIME 5.f

#define PLAYER_ROTATION_SPEED 400.f
#define PURPLE_MAX 100

typedef struct Player
{
	sfTexture* texture;
	sfSprite* sprite;
	sfBool canShoot;
	float cooldown;
	sfVector2f velocity;
	int health;
	float invincibleTime;
	sfTexture* shieldTexture;
	sfSprite* shieldSprite;
	sfBool shieldActive;
	sfSoundBuffer* deathBuffer;
	sfSound* deathSound;
	sfSoundBuffer* bufferShoot;
	sfSound* shootSound;
	sfSoundBuffer* bufferLifeUp;
	sfSound* lifeUpSound;
	int purpleCharge;
	sfBool purpleAvailable;
}Player;

//* @brief Function to get the player's health.
//* @return The player's health.
int GetPlayerHealth(void);

//* @brief Function to increase player's charge.
void IncreasePurple();

//* @brief Function to get player's charge.
int GetPurple();

//* @brief Function to load the player.
void LoadPlayer(void);

//* @brief Function to update the player.
//* @param _dt Delta time.
void UpdatePlayer(float _dt);

//* @brief Function to draw the player.
//* @param _renderWindow The render window.
void DrawPlayer(sfRenderWindow* const _renderWindow);

//* @brief Function to clean up the player.
void CleanupPlayer(void);

#endif // !PLAYER_H
