#include "Player.h"

Player player;

void MovePlayer(float _dt);
void UpdateCooldown(float _dt);
void UpdateFireControl(void);

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
		return;
	}
	player.sprite = sfSprite_create();
	if (!player.sprite)
	{
		printf("Error creating player sprite\n");
		player.texture = NULL;
		return;
	}
	sfSprite_setTexture(player.sprite, player.texture, sfTrue);
	sfFloatRect playerHitbox = sfSprite_getLocalBounds(player.sprite);
	sfSprite_setOrigin(player.sprite, (sfVector2f) { playerHitbox.width / 2, playerHitbox.height / 2 });
	sfSprite_setPosition(player.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	player.canShoot = sfTrue;
	player.cooldown = FIRE_RATE;
	player.direction = (sfVector2f){ 0, 0 };
	player.health = PLAYER_HEALTH;
}

void UpdatePlayer(float _dt)
{
	MovePlayer(_dt);
	UpdateCooldown(_dt);
	UpdateFireControl();
}

void DrawPlayer(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, player.sprite, NULL);
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
	int rotation = 0;
	if (sfKeyboard_isKeyPressed(sfKeyD))
	{
		rotation = 5;
	}
	if (sfKeyboard_isKeyPressed(sfKeyQ))
	{
		rotation = -5;
	}

	sfSprite_rotate(player.sprite, (float)rotation);

	if (sfKeyboard_isKeyPressed(sfKeyZ))
	{
		sfVector2f newDirection = (sfVector2f){
			sinf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180)),
			-cosf(sfSprite_getRotation(player.sprite) * (float)(M_PI / 180))
		};

		player.direction = (sfVector2f){ newDirection.x + player.direction.x, newDirection.y + player.direction.y };

		if (player.direction.x > MAX_ACCELERATE_FORCE)
			player.direction.x = MAX_ACCELERATE_FORCE;
		else if (player.direction.x < -MAX_ACCELERATE_FORCE)
			player.direction.x = -MAX_ACCELERATE_FORCE;

		if (player.direction.y > MAX_ACCELERATE_FORCE)
			player.direction.y = MAX_ACCELERATE_FORCE;
		else if (player.direction.y < -MAX_ACCELERATE_FORCE)
			player.direction.y = -MAX_ACCELERATE_FORCE;
	}

	sfSprite_move(player.sprite, (sfVector2f) { player.direction.x* PLAYER_BASE_SPEED* _dt, player.direction.y* PLAYER_BASE_SPEED* _dt });
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
			sfVector2f shotPosition = { playerHitbox.left + playerHitbox.width / 2, playerHitbox.top };
			AddBullet(shotPosition);

			player.canShoot = sfFalse;
		}
	}
}
