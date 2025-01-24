#include "Game.h"

void LoadGame(void)
{
	LoadPlayer();
	LoadBullet();
}

void KeyPressedGame(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
		break;
	case sfKeySpace:
		break;
	default:
		break;
	}
}

void UpdateGame(sfRenderWindow* const _renderWindow, float _dt)
{
	UpdatePlayer(_dt);
	UpdateBullet(_dt);
}

void DrawGame(sfRenderWindow* const _renderWindow)
{
	DrawBullet(_renderWindow);
	DrawPlayer(_renderWindow);
}

void CleanupGame(void)
{
	CleanupPlayer();
	CleanupBullet();
}
