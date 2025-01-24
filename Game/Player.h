#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"

#define PLAYER_BASE_SPEED 5
#define MAX_ACCELERATE_FORCE 40
#define FIRE_RATE 0.15f

typedef struct Player
{
	sfTexture* texture;
	sfSprite* sprite;
	sfBool canShoot;
	float cooldown;
	sfVector2f direction;
}Player;

void LoadPlayer(void);
void UpdatePlayer(float _dt);
void DrawPlayer(sfRenderWindow* const _renderWindow);
void CleanupPlayer(void);

#endif // !PLAYER_H
