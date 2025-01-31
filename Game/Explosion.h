#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Common.h"
#include "Animations.h"
#include "Wraparound.h"
#include "HollowPurple.h"

void LoadExplosion(void);
void CreateExplosion(sfVector2f _pos);
void UpdateExplosion(float _dt);
void DrawExplosion(sfRenderWindow* _render);
void CleanUpExplosion(void);
#endif // !EXPLOSION_H
