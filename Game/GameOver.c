#include "GameOver.h"

void LoadGameOver(void)
{
}

void KeyPressedGameOver(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		CleanupGameOver();
		LoadMenu();
		SetGameState(MENU);
		break;
	case sfKeySpace:
		CleanupGameOver();
		LoadGame();
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
}

void CleanupGameOver(void)
{
}
