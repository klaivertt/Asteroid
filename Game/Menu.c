#include "Menu.h"

MenuData menuData;

void LoadMenu(void)
{
}

void KeyPressedMenu(sfRenderWindow* const _renderWindow, sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		sfRenderWindow_close(_renderWindow);
		break;
	case sfKeySpace:
		SetGameState(GAME);
		break;
	default:
		break;
	}
}

void UpdateMenu(sfRenderWindow* const _renderWindow, float _dt)
{
}

void DrawMenu(sfRenderWindow* const _renderWindow)
{
}

void CleanupMenu(void)
{
}
