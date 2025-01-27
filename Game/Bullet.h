#ifndef BULLET_H
#define BULLET_H

#include "Common.h"

#define BULLET_MAX 200
#define BULLET_SPEED 650.f

typedef struct Bullet
{
	sfSprite* sprite;
	sfVector2f velocity;
	float lifeTime;
}Bullet;

void LoadBullet(void);
void UpdateBullet(float _dt);
void DrawBullet(sfRenderWindow* const _renderWindow);
void CleanupBullet(void);

unsigned int GetBulletNumb(void);
void AddBullet(sfVector2f _position, sfVector2f _direction);

#endif // !BULLET_H
