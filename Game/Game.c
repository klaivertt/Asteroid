#include "Game.h"
#include "Player.h"

Game game = { 0 };

void LoadBackground();

#pragma region CoreGame
void LoadGame(void)
{

}

void UpdateGame(float _dt, sfRenderWindow* _render)
{
	UpdatePlayer(_dt);
}

void OnKeyPressedGame(sfKeyEvent _key, sfRenderWindow* _render)
{
	OnKeyPressedPlayer(_key);
	switch (_key.code)
	{
	default:
		break;
	}
}

void OnMousePressedGame(sfMouseButtonEvent _mouse, sfRenderWindow* _render)
{
}

void DrawGame(sfRenderWindow* _render)
{
	DrawPlayer(_render);
}


void CleanupGame()
{

}

#pragma endregion

void LoadBackground()
{

}