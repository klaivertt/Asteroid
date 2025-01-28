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
}Player;

//* @brief Function to get the player's health.
//* @return The player's health.
int GetPlayerHealth(void);

void LoadPlayer(void);
void UpdatePlayer(float _dt);
void DrawPlayer(sfRenderWindow* const _renderWindow);
void CleanupPlayer(void);

#endif // !PLAYER_H
