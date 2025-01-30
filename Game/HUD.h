#ifndef HUD_H
#define HUD_H

#include "Common.h"

#include "Player.h"
#include "Text.h"
#include "Score.h"

typedef struct HUDData
{
	sfText* textScore;
	sfSprite* healthBar[PLAYER_MAX_HEALTH];
	sfTexture* emptylLifeTexture;
	sfTexture* fullLifeTexture;
	sfSprite* purplePower;
	sfTexture* purpleTexture;
	sfSprite* bar;
	sfTexture* barTexture;
	sfSprite* barFull;
	sfTexture* barFullTexture;

}HUDData;

//* @brief Load the HUD
void LoadHud(void);

//* @brief Update the HUD
//* @param _dt Delta time
void UpdateHud(float _dt);

//* @brief Draw the HUD
//* @param _renderWindow The window to draw the HUD
void DrawHud(sfRenderWindow* const _renderWindow);

//* @brief Cleanup the HUD
void CleanupHud(void);

#endif // !HUD_H
