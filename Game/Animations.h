#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <SFML/Graphics.h>

typedef struct Anim
{
	sfTexture* texture;
	sfSprite* sprite;
	sfIntRect size;
	int frameCount;
	int frameRate;
	int currentFrame;
	float timer;
	sfVector2f start;
	sfBool isLooping;
	sfBool isFinished;
}Anim;

//* @brief Create an animation
void CreateAnimation(Anim* _anim, char* const _filepath, int _maxFrame, int _frameCount, int _frameRate, sfBool _isLooping, sfVector2f _start);
void UpdateAnimation(Anim* _anim, float _dt);
void ResetAnimation(Anim* _anim);
void CleanUpAnimation(Anim* _anim);

#endif // !ANIMATIONS_H