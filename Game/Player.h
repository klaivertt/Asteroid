#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "Bullet.h"

#define PLAYER_SPEED 600
#define FIRE_RATE 0.1f

typedef struct Player
{
	sfTexture* texture;
	sfSprite* sprite;
	sfBool canShoot;
	float cooldown;
}Player;

void LoadPlayer(void);
void UpdatePlayer(float _dt);
void DrawPlayer(sfRenderWindow* const _renderWindow);
void CleanupPlayer(void);

#endif // !PLAYER_H
