#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"
#include "Wraparound.h"

#define PLAYER_BASE_SPEED 5
#define MAX_ACCELERATE_FORCE 40
#define FIRE_RATE 0.1f
#define PLAYER_HEALTH 3
#define PLAYER_MAX_HEALTH 9

typedef struct Player
{
	sfTexture* texture;
	sfSprite* sprite;
	sfBool canShoot;
	float cooldown;
	sfVector2f velocity;
	int health;
}Player;

//* @brief Function to get the player's health.
//* @return The player's health.
int GetPlayerHealth(void);

void LoadPlayer(void);
void UpdatePlayer(float _dt);
void DrawPlayer(sfRenderWindow* const _renderWindow);
void CleanupPlayer(void);

#endif // !PLAYER_H
