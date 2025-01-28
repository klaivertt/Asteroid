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
}HUDData;

void LoadHud(void);
void UpdateHud(float _dt);
void DrawHud(sfRenderWindow* const _renderWindow);
void CleanupHud(void);
#endif // !HUD_H
