#include "GameState.h"

GameState gameState;

void SetGameState(GameState _gameState)
{
	switch (gameState)
	{
	case MENU:
		CleanupMenu();
		break;

	case GAME:
		CleanupGame();
		break;

	case GAME_OVER:
		CleanupGameOver();
		break;
	}

	gameState = _gameState;

	switch (gameState)
	{
	case MENU:
		LoadMenu();
		break;

	case GAME:
		LoadGame();
		break;

	case GAME_OVER:
		LoadGameOver();
		break;
	}
}

GameState GetGameState(void)
{
	return gameState;
}
