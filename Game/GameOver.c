#include "GameOver.h"

GameOverData gameOverData = { 0 };

void LoadGameOver(void)
{
	gameOverData.texture = sfTexture_createFromFile("Assets/Sprites/Background/3b.png", NULL);
	if (!gameOverData.texture)
	{
		printf("Error loading game over texture\n");
		exit(EXIT_FAILURE);
	}
	gameOverData.sprite = sfSprite_create();
	if (!gameOverData.sprite)
	{
		printf("Error creating game over sprite\n");
		gameOverData.texture = NULL;
		exit(EXIT_FAILURE);
	}
	sfSprite_setTexture(gameOverData.sprite, gameOverData.texture, sfTrue);
	sfSprite_setScale(gameOverData.sprite, (sfVector2f) { 2, 2 });
	sfFloatRect gameOverHitbox = sfSprite_getLocalBounds(gameOverData.sprite);
	sfSprite_setOrigin(gameOverData.sprite, (sfVector2f) { gameOverHitbox.width / 2, gameOverHitbox.height / 2 });
	sfSprite_setPosition(gameOverData.sprite, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	gameOverData.gameOverText = InitText("Game Over", 65, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.3f });
	gameOverData.scoreText = InitTextWithValue("Score: %d", GetScore(), 35, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	gameOverData.highScoreText = InitTextWithValue("High Score: %d", GetHighScore(), 35, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50 });
	gameOverData.pressSpaceText = InitText("Press Space to Play Again", 35, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100 });
	gameOverData.pressEscapeText = InitText("Press Escape to Return to Menu", 35, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150 });

	SetTextOrigin(gameOverData.gameOverText, (sfVector2f) { 2, 2 });
	SetTextOrigin(gameOverData.scoreText, (sfVector2f) { 2, 2 });
	SetTextOrigin(gameOverData.highScoreText, (sfVector2f) { 2, 2 });
	SetTextOrigin(gameOverData.pressSpaceText, (sfVector2f) { 2, 2 });
	SetTextOrigin(gameOverData.pressEscapeText, (sfVector2f) { 2, 2 });
}

void KeyPressedGameOver(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
		break;
	case sfKeySpace:
		SetGameState(GAME);
		break;
	default:
		break;
	}
}

void UpdateGameOver(sfRenderWindow* const _renderWindow, float _dt)
{
}

void DrawGameOver(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, gameOverData.sprite, NULL);
	DrawText(_renderWindow, gameOverData.gameOverText);
	DrawText(_renderWindow, gameOverData.scoreText);
	DrawText(_renderWindow, gameOverData.highScoreText);
	DrawText(_renderWindow, gameOverData.pressSpaceText);
	DrawText(_renderWindow, gameOverData.pressEscapeText);
}

void CleanupGameOver(void)
{
}
