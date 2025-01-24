#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Game.h"
#include "Menu.h"
#include "GameOver.h"

#pragma region Enum
typedef enum GameState
{
	MENU,
	GAME,
	GAME_OVER
}GameState;
#pragma endregion

//* @brief Function to set the current game state.
//* This function sets the current game state to the one passed as a parameter. 
//* And calls the corresponding function to load the resources for that state and clean up the resources of the previous state.
//* @param _gameState The game state to set.
void SetGameState(GameState _gameState);

//* @brief Function to get the current game state.
//* This function returns the current game state.
GameState GetGameState(void);

#endif // !GAME_STATE_H
