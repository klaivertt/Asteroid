#include "Explosion.h"

Anim explosion[100] = { 0 };
unsigned int explosionCount;

void DestroyExplosion(unsigned int _index);

void LoadExplosion(void)
{
	explosionCount = 0;
}

void CreateExplosion(sfVector2f _pos)
{
	CreateAnimation(&explosion[explosionCount], "Assets/Sprites/FX/Fx8.png", 7, 7, 15, sfFalse, (sfVector2f) { 0, 0 });
	sfFloatRect globalBounds = sfSprite_getGlobalBounds(explosion[explosionCount].sprite);
	sfSprite_setOrigin(explosion[explosionCount].sprite, (sfVector2f) { globalBounds.width / 2, globalBounds.height / 2 });
	sfSprite_setPosition(explosion[explosionCount].sprite, _pos);
	explosionCount++;
}

void UpdateExplosion(float _dt)
{
	for (int i = explosionCount - 1; i >= 0; i--)
	{
		if (explosion[i].isFinished)
		{
			DestroyExplosion(i);
		}
		UpdateAnimation(&explosion[i], _dt);
	}
}

void DrawExplosion(sfRenderWindow* _render)
{
	for (int i = explosionCount - 1; i >= 0; i--)
	{
		DrawWraparound(_render, explosion[i].sprite);
	}
}

void CleanUpExplosion(void)
{
	for (int i = explosionCount - 1; i >= 0; i--)
	{
		CleanUpAnimation(&explosion[i]);
	}
}

void DestroyExplosion(unsigned int _index)
{
	CleanUpAnimation(&explosion[_index]);

	for (unsigned int i = _index; i < explosionCount - 1; i++)
	{
		Anim temp = { 0 };
		temp = explosion[i];
		explosion[i] = explosion[i + 1];
		explosion[i + 1] = temp;
	}

	explosionCount--;
}