#include "Player.h"

Player player;

void MovePlayer(float _dt);
void UpdateCooldown(float _dt);
void UpdateFireControl(void);
void lifeUpdate(void);
void ColidingWithAsteroid(void);

int GetPlayerHealth(void)
{
	return player.health;
}

void LoadPlayer(void)
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
	sfSprite_setTexture(player.sprite, player.texture, sfTrue);
	sfFloatRect playerHitbox = sfSprite_getLocalBounds(player.sprite);
	sfSprite_setOrigin(player.sprite, (sfVector2f) { playerHitbox.width / 2, playerHitbox.height / 2 });
	sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	player.canShoot = sfTrue;
	player.cooldown = FIRE_RATE;
	player.velocity = (sfVector2f){ 0, 0 };
	player.health = PLAYER_HEALTH;
}

void UpdatePlayer(float _dt)
{
	MovePlayer(_dt);
	UpdateCooldown(_dt);
	UpdateFireControl();
	lifeUpdate();
	ColidingWithAsteroid();
}

void DrawPlayer(sfRenderWindow* const _renderWindow)
{
	DrawWraparound(_renderWindow, player.sprite);
}

void CleanupPlayer(void)
{
	sfTexture_destroy(player.texture);
	player.texture = NULL;

	sfSprite_destroy(player.sprite);
	player.sprite = NULL;
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

			player.canShoot = sfFalse;
		}
	}
}

void lifeUpdate(void)
{
	if (GetScoreLife() > 5000)
	{
		RemovetScoreLife();
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
			sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
			player.health--;
			if (player.health <= 0)
			{
				player.health = 0;
			}
		}
	}
}