#include "Player.h"

Player player;

void LoadSprite(void);
void LoadSound(void);
void MovePlayer(float _dt);
void UpdateCooldown(float _dt);
void UpdateFireControl(void);
void lifeUpdate(void);
void ColidingWithAsteroid(void);
void UpdateShield(float _dt);

int GetPlayerHealth(void)
{
	return player.health;
}


void LoadPlayer(void)
{
	LoadSprite();
	LoadSound();

	player.canShoot = sfTrue;
	player.cooldown = FIRE_RATE;
	player.velocity = (sfVector2f){ 0, 0 };
	player.health = PLAYER_HEALTH;
	player.invincibleTime = 0;
	player.shieldActive = sfFalse;
}

void UpdatePlayer(float _dt)
{
	MovePlayer(_dt);
	SetPlayerPosition(sfSprite_getPosition(player.sprite));
	UpdateCooldown(_dt);
	UpdateFireControl();
	lifeUpdate();
	UpdateShield(_dt);
	ColidingWithAsteroid();
}

void DrawPlayer(sfRenderWindow* const _renderWindow)
{
	DrawWraparound(_renderWindow, player.sprite);
	if (player.shieldActive)
	{
		DrawWraparound(_renderWindow, player.shieldSprite);
	}
}

void CleanupPlayer(void)
{
	sfTexture_destroy(player.texture);
	player.texture = NULL;

	sfSprite_destroy(player.sprite);
	player.sprite = NULL;
}

void LoadSprite(void)
{
	player.texture = sfTexture_createFromFile("Assets/Sprites/Ship/3.png", NULL);
	if (!player.texture)
	{
		printf("Error loading player texture\n");
		exit(EXIT_FAILURE);
	}
	player.sprite = sfSprite_create();
	if (!player.sprite)
	{
		printf("Error creating player sprite\n");
		player.texture = NULL;
		exit(EXIT_FAILURE);
	}

	player.shieldTexture = sfTexture_createFromFile("Assets/Sprites/FX/Shield.png", NULL);
	if (!player.shieldTexture)
	{
		printf("Error loading shield texture\n");
		exit(EXIT_FAILURE);
	}
	player.shieldSprite = sfSprite_create();
	if (!player.shieldSprite)
	{
		printf("Error creating shield sprite\n");
		player.shieldTexture = NULL;
		exit(EXIT_FAILURE);
	}

	sfSprite_setTexture(player.sprite, player.texture, sfTrue);
	sfFloatRect playerHitbox = sfSprite_getLocalBounds(player.sprite);
	sfSprite_setOrigin(player.sprite, (sfVector2f) { playerHitbox.width / 2, playerHitbox.height / 2 });
	sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	sfSprite_setTexture(player.shieldSprite, player.shieldTexture, sfTrue);
	sfFloatRect shieldHitbox = sfSprite_getLocalBounds(player.shieldSprite);
	sfSprite_setOrigin(player.shieldSprite, (sfVector2f) { shieldHitbox.width / 2, shieldHitbox.height / 2 });
	sfSprite_setPosition(player.shieldSprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
}

void LoadSound(void)
{
	player.deathBuffer = sfSoundBuffer_createFromFile("Assets/Sounds/Death.wav");
	if (!player.deathBuffer)
	{
		printf("Error loading death sound\n");
		exit(EXIT_FAILURE);
	}
	player.deathSound = sfSound_create();
	if (!player.deathSound)
	{
		printf("Error creating death sound\n");
		player.deathBuffer = NULL;
		exit(EXIT_FAILURE);
	}
	sfSound_setBuffer(player.deathSound, player.deathBuffer);

	player.bufferShoot = sfSoundBuffer_createFromFile("Assets/Sounds/2.wav");
	if (!player.bufferShoot)
	{
		printf("Error loading shoot sound\n");
		exit(EXIT_FAILURE);
	}

	player.shootSound = sfSound_create();
	sfSound_setVolume(player.shootSound, 70);

	if (!player.shootSound)
	{
		printf("Error creating shoot sound\n");
		player.bufferShoot = NULL;
		exit(EXIT_FAILURE);
	}
	sfSound_setBuffer(player.shootSound, player.bufferShoot);

	player.bufferLifeUp = sfSoundBuffer_createFromFile("Assets/Sounds/Gold1.wav");
	if (!player.bufferLifeUp)
	{
		printf("Error loading life up sound\n");
		exit(EXIT_FAILURE);
	}

	player.lifeUpSound = sfSound_create();
	if (!player.lifeUpSound)
	{
		printf("Error creating life up sound\n");
		player.bufferLifeUp = NULL;
		exit(EXIT_FAILURE);
	}
	sfSound_setBuffer(player.lifeUpSound, player.bufferLifeUp);
}

void MovePlayer(float _dt)
{
	float rotation = 0;
	if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
	{
		rotation = 300.f * _dt;
	}
	if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft))
	{
		rotation = -300.f * _dt;
	}

	sfSprite_rotate(player.sprite, rotation);

	if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp))
	{
		sfVector2f newDirection = (sfVector2f){
			sinf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180)),
			-cosf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180))
		};

		player.velocity = (sfVector2f){ newDirection.x + player.velocity.x, newDirection.y + player.velocity.y };

		if (player.velocity.x > MAX_ACCELERATE_FORCE)
		{
			player.velocity.x = MAX_ACCELERATE_FORCE;
		}
		else if (player.velocity.x < -MAX_ACCELERATE_FORCE)
		{
			player.velocity.x = -MAX_ACCELERATE_FORCE;
		}

		if (player.velocity.y > MAX_ACCELERATE_FORCE)
		{
			player.velocity.y = MAX_ACCELERATE_FORCE;
		}
		else if (player.velocity.y < -MAX_ACCELERATE_FORCE)
		{
			player.velocity.y = -MAX_ACCELERATE_FORCE;
		}
	}

	sfSprite_move(player.sprite, (sfVector2f) { player.velocity.x* PLAYER_BASE_SPEED* _dt, player.velocity.y* PLAYER_BASE_SPEED* _dt });

	sfVector2f playerPosition = sfSprite_getPosition(player.sprite);
	if (playerPosition.x < 0)
	{
		sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH, playerPosition.y });
	}
	else if (playerPosition.x > SCREEN_WIDTH)
	{
		sfSprite_setPosition(player.sprite, (sfVector2f) { 0, playerPosition.y });
	}
	if (playerPosition.y < 0)
	{
		sfSprite_setPosition(player.sprite, (sfVector2f) { playerPosition.x, SCREEN_HEIGHT });
	}
	else if (playerPosition.y > SCREEN_HEIGHT)
	{
		sfSprite_setPosition(player.sprite, (sfVector2f) { playerPosition.x, 0 });
	}
}

void UpdateCooldown(float _dt)
{
	if (!player.canShoot)
	{
		player.cooldown -= _dt;
		if (player.cooldown < 0)
		{
			player.cooldown = FIRE_RATE;
			player.canShoot = sfTrue;
		}
	}
}

void UpdateFireControl(void)
{
	if (sfKeyboard_isKeyPressed(sfKeySpace))
	{
		if (player.canShoot && GetBulletNumb() < BULLET_MAX)
		{
			sfFloatRect playerHitbox = sfSprite_getGlobalBounds(player.sprite);
			sfVector2f shotPosition = { playerHitbox.left + playerHitbox.width / 2, playerHitbox.top + playerHitbox.height / 2 };

			sfVector2f direction = (sfVector2f){
			sinf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180)),
			-cosf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180))
			};
			AddBullet(shotPosition, direction);
			sfSound_play(player.shootSound);

			player.canShoot = sfFalse;
		}
	}
}

void lifeUpdate(void)
{
	if (GetScoreLife() > 5000)
	{
		RemovetScoreLife();

		if (player.health < PLAYER_MAX_HEALTH)
		{
			sfSound_play(player.lifeUpSound);
		}

		player.health++;
		if (player.health > PLAYER_MAX_HEALTH)
		{
			player.health = PLAYER_MAX_HEALTH;
		}
	}
}

void ColidingWithAsteroid(void)
{
	Asteroid* asteroids = GetAsteroids();
	unsigned int asteroidNumb = GetAsteroidNumb();

	for (unsigned int i = 0; i < asteroidNumb; i++)
	{
		if (!asteroids[i].sprite)
		{
			continue;
		}

		sfFloatRect playerHitbox = sfSprite_getGlobalBounds(player.sprite);
		sfFloatRect asteroidHitbox = sfSprite_getGlobalBounds(asteroids[i].sprite);

		sfVector2f playerPosition = sfSprite_getPosition(player.sprite);
		sfVector2f asteroidPosition = sfSprite_getPosition(asteroids[i].sprite);

		if (ColisionCircleCircle(playerPosition, playerHitbox.width / 2, asteroidPosition, asteroidHitbox.width / 2))
		{
			DestroyAsteroid(i);
			if (!player.shieldActive)
			{
				sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
				player.velocity = (sfVector2f) { 0, 0 };
				player.health--;
				player.shieldActive = sfTrue;
				sfSound_play(player.deathSound);
				if (player.health <= 0)
				{
					player.health = 0;
				}
			}

		}
	}
}

void UpdateShield(float _dt)
{
	if (player.shieldActive)
	{
		sfSprite_setPosition(player.shieldSprite, sfSprite_getPosition(player.sprite));
		player.invincibleTime += _dt;
		if (player.invincibleTime > SHIELD_TIME)
		{
			player.invincibleTime = 0;
			player.shieldActive = sfFalse;
		}
	}
}