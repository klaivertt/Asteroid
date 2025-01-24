#include "Bullet.h"

sfTexture* bulletTexture;
Bullet bulletList[BULLET_MAX];
unsigned int bulletCount;

void SortBulletList(unsigned int _index);

void LoadBullet(void)
{
	bulletTexture = sfTexture_createFromFile("Assets/Sprites/Shot.png", NULL);
	bulletCount = 0;
}

void UpdateBullet(float _dt)
{
	for (int i = bulletCount - 1; i >= 0; i--)
	{
		// Bullet move
		sfSprite_move(bulletList[i].sprite, (sfVector2f) { bulletList[i].velocity.x * _dt, bulletList[i].velocity.y * _dt });

		// The bullet is outside the screen
		sfFloatRect hitbox = sfSprite_getGlobalBounds(bulletList[i].sprite);
		if (hitbox.top + hitbox.height < 0)
		{
			sfSprite_destroy(bulletList[i].sprite);
			bulletList[i].sprite = NULL;
			SortBulletList(i);
		}
	}

	printf("nombre de tirs : %u\n", bulletCount);
}

void DrawBullet(sfRenderWindow* const _renderWindow)
{
	for (unsigned int i = 0; i < bulletCount; i++)
	{
		sfRenderWindow_drawSprite(_renderWindow, bulletList[i].sprite, NULL);
	}
}

void CleanupBullet(void)
{
	sfTexture_destroy(bulletTexture);
	bulletTexture = NULL;

	for (unsigned int i = 0; i < bulletCount; i++)
	{
		sfSprite_destroy(bulletList[i].sprite);
		bulletList[i].sprite = NULL;
	}
}

unsigned int GetBulletNumb(void)
{
	return bulletCount;
}

void AddBullet(sfVector2f _position)
{
	Bullet newBullet = { 0 };

	newBullet.sprite = sfSprite_create();
	sfSprite_setTexture(newBullet.sprite, bulletTexture, sfTrue);
	sfFloatRect hitbox = sfSprite_getLocalBounds(newBullet.sprite);
	sfSprite_setOrigin(newBullet.sprite, (sfVector2f) { hitbox.width / 2, hitbox.height / 2 });
	sfSprite_setPosition(newBullet.sprite, _position);

	newBullet.velocity = (sfVector2f){ 0, -BULLET_SPEED };

	bulletList[bulletCount] = newBullet;
	bulletCount++;
}

void SortBulletList(unsigned int _index)
{
	for (unsigned int i = _index; i < bulletCount - 1; i++)
	{
		Bullet temp = bulletList[i];
		bulletList[i] = bulletList[i + 1];
		bulletList[i + 1] = temp;
	}

	bulletCount--;
}
