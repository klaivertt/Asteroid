#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "GameState.h"
#include "Menu.h"
#include "GameOver.h"

#include "Player.h"
#include "Bullet.h"
#include "HUD.h"
#include "Asteroid.h"
#include "Score.h"
#include "Explosion.h"

//* @brief Load the game
void LoadGame(void);

//* @brief Handle the game events
//* @param _event The event to handle
void KeyPressedGame(sfKeyEvent _key);

//* @brief Update the game
//* @param _renderWindow The window to update the game
//* @param _dt Delta time
void UpdateGame(sfRenderWindow* const _renderWindow, float _dt);

//* @brief Draw the game
//* @param _renderWindow The window to draw the game
void DrawGame(sfRenderWindow* const _renderWindow);

//* @brief Cleanup the game
void CleanupGame(void);
#endif // !GAME_H
