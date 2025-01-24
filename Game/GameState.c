#include "GameState.h"

#include "../Game/Menu/Menu.h"
#include "./Game/Game.h"

GameState state;

void SetGameState(GameState _state)
{
	switch (state)
	{
	case GAME:
		CleanupGame();
		break;

	case MENU:

		CleanupMenu();
		break;
	}

	state = _state;

	switch (state)
	{
	case GAME:

		LoadGame();
		break;

	case MENU:

		LoadMenu();
		break;
	}
}

GameState GetGameState(void)
{
    return state;
}