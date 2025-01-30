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

//* @brief Load the bullet
void LoadBullet(void);

//* @brief Update the bullet
//* @param _dt Delta time
void UpdateBullet(float _dt);

//* @brief Draw the bullet
//* @param _renderWindow The window to draw the bullet
void DrawBullet(sfRenderWindow* const _renderWindow);

//* @brief Cleanup the bullet
void CleanupBullet(void);

//* @brief Get the bullets table
//* @return The bullets table
unsigned int GetBulletNumb(void);

//* @brief Add a bullet
//* @param _position The position of the bullet
//* @param _direction The direction of the bullet
void AddBullet(sfVector2f _position, sfVector2f _direction);

//* @brief Get the bullets table
//* @return The bullets table
Bullet* GetBullets(void);

//* @brief Remove a bullet
//* @param _i The index of the bullet to remove
void RemoveBullet(unsigned int _i);
#endif // !BULLET_H
