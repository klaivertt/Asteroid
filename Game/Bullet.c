#include "Bullet.h"

sfTexture* bulletTexture;
Bullet bulletList[BULLET_MAX];
sfSoundBuffer* bufferShoot;
unsigned int bulletCount;

void SortBulletList(unsigned int _index);

void LoadBullet(void)
{
	if (GetHollowPurpleIsActivated())
	{
		bulletTexture = sfTexture_createFromFile("Assets/Sprites/Shoot/purple.png", NULL);
	}
	else
	{
		bulletTexture = sfTexture_createFromFile("Assets/Sprites/Shoot/4.png", NULL);
	}

	if (GetHollowPurpleIsActivated())
	{
		bufferShoot = sfSoundBuffer_createFromFile("Assets/Sounds/Rikogetsshotinthehead byToji.wav");
	}
	else
	{
		bufferShoot = sfSoundBuffer_createFromFile("Assets/Sounds/2.wav");
	}
	bulletCount = 0;
}

void UpdateBullet(float _dt)
{
	for (int i = bulletCount - 1; i >= 0; i--)
	{
		// Bullet move
		sfSprite_move(bulletList[i].sprite, (sfVector2f) { bulletList[i].velocity.x* _dt, bulletList[i].velocity.y* _dt });

		sfVector2f bulletPosition = sfSprite_getPosition(bulletList[i].sprite);
		if (bulletPosition.x < 0)
		{
			sfSprite_setPosition(bulletList[i].sprite, (sfVector2f) { SCREEN_WIDTH, bulletPosition.y });
		}
		else if (bulletPosition.x > SCREEN_WIDTH)
		{
			sfSprite_setPosition(bulletList[i].sprite, (sfVector2f) { 0, bulletPosition.y });
		}
		if (bulletPosition.y < 0)
		{
			sfSprite_setPosition(bulletList[i].sprite, (sfVector2f) { bulletPosition.x, SCREEN_HEIGHT });
		}
		else if (bulletPosition.y > SCREEN_HEIGHT)
		{
			sfSprite_setPosition(bulletList[i].sprite, (sfVector2f) { bulletPosition.x, 0 });
		}

		// Bullet life time
		bulletList[i].lifeTime -= _dt;
		if (bulletList[i].lifeTime < 0)
		{
			sfSprite_destroy(bulletList[i].sprite);
			bulletList[i].sprite = NULL;
			sfSound_destroy(bulletList[i].sound);
			bulletList[i].sound = NULL;
			SortBulletList(i);
		}
	}

	//printf("nombre de tirs : %u\n", bulletCount);
}

void DrawBullet(sfRenderWindow* const _renderWindow)
{
	for (int i = bulletCount - 1; i >= 0; i--)
	{
		if (!bulletList[i].sprite)
		{
			continue;
		}
		sfRenderWindow_drawSprite(_renderWindow, bulletList[i].sprite, NULL);
	}
}

void CleanupBullet(void)
{
	sfTexture_destroy(bulletTexture);
	bulletTexture = NULL;

	for (int i = bulletCount - 1; i >= 0; i--)
	{
		sfSprite_destroy(bulletList[i].sprite);
		bulletList[i].sprite = NULL;
	}
}

unsigned int GetBulletNumb(void)
{
	return bulletCount;
}

void AddBullet(sfVector2f _position, sfVector2f _direction)
{
	Bullet newBullet = { 0 };

	newBullet.sprite = sfSprite_create();
	sfSprite_setTexture(newBullet.sprite, bulletTexture, sfTrue);
	sfFloatRect hitbox = sfSprite_getLocalBounds(newBullet.sprite);
	sfSprite_setOrigin(newBullet.sprite, (sfVector2f) { hitbox.width / 2, hitbox.height / 2 });
	sfVector2f newDirection;
	newDirection = (sfVector2f){ _direction.x, _direction.y };
	sfSprite_setPosition(newBullet.sprite, _position);

	newBullet.velocity = (sfVector2f){ _direction.x * BULLET_SPEED, _direction.y * BULLET_SPEED };

	newBullet.sound = sfSound_create();
	sfSound_setBuffer(newBullet.sound, bufferShoot);
	if (GetHollowPurpleIsActivated())
	{
		sfSound_setVolume(newBullet.sound, 40);
	}
	else
	{
		sfSound_setVolume(newBullet.sound, 60);
	}
	sfSound_play(newBullet.sound);
	newBullet.lifeTime = 2.5f;
	bulletList[bulletCount] = newBullet;
	bulletCount++;
}

void SortBulletList(unsigned int _index)
{
	for (unsigned int i = _index; i < bulletCount - 1; i++)
	{
		Bullet temp = { 0 };
		temp = bulletList[i];
		bulletList[i] = bulletList[i + 1];
		bulletList[i + 1] = temp;
	}
	bulletCount--;
}

Bullet* GetBullets(void)
{
	return bulletList;
}

void RemoveBullet(unsigned int _i)
{
	sfSprite_destroy(bulletList[_i].sprite);
	bulletList[_i].sprite = NULL;
	SortBulletList(_i);
}