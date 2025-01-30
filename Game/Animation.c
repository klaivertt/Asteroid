#include "Animations.h"


void CreateAnimation(Anim* _anim, char* const _filepath, int _maxFrame, int _frameCount, int _frameRate, sfBool _isLooping, sfVector2f _start)
{
	// Fonction qui permet de charger et stocker une animation
	_anim->texture = sfTexture_createFromFile(_filepath, NULL);
	_anim->sprite = sfSprite_create();

	sfSprite_setTexture(_anim->sprite, _anim->texture, sfTrue);
	sfIntRect rect = sfSprite_getTextureRect(_anim->sprite);

	rect.width = rect.width / _maxFrame;
	rect.left = (int) _start.x * rect.width;
	rect.top = (int) _start.y * rect.height;

	sfSprite_setTextureRect(_anim->sprite, rect);

	_anim->size = rect;
	_anim->timer = 0.0f;
	_anim->currentFrame = 1;
	_anim->frameCount = _frameCount;
	_anim->frameRate = _frameRate;
	_start.x = _start.x * (float) rect.width;
	_start.y = _start.y * (float) rect.height;
	_anim->start = _start;
	_anim->isLooping = _isLooping;
	_anim->isFinished = sfFalse;
}

void UpdateAnimation(Anim* _anim, float _dt)
{
	// Fonction appelé toutes les frames pour mettre à jour l'animation actuelle
	_anim->timer += _dt;
	if (_anim->timer >= 1.0f / _anim->frameRate)
	{
		if (_anim->currentFrame == _anim->frameCount)
		{
			if (_anim->isLooping == sfTrue)
			{
				_anim->currentFrame = 1;
				_anim->timer = _anim->timer - (1.0f / _anim->frameRate);

				sfIntRect rect = sfSprite_getTextureRect(_anim->sprite);

				rect.left = (int)_anim->start.x + rect.width * (_anim->currentFrame - 1);

				sfSprite_setTextureRect(_anim->sprite, rect);
			}
			else
			{
				_anim->isFinished = sfTrue;
			}
		}
		else
		{
			_anim->currentFrame += 1;
			_anim->timer = _anim->timer - (1.0f / _anim->frameRate);

			sfIntRect rect = sfSprite_getTextureRect(_anim->sprite);

			rect.left = (int)_anim->start.x + rect.width * (_anim->currentFrame - 1);

			sfSprite_setTextureRect(_anim->sprite, rect);
		}
	}
}

void ResetAnimation(Anim* _anim)
{
	// Fonction appelé pour réinitialiser une animation à son état de base
	_anim->currentFrame = 1;
	_anim->timer = 0;
	_anim->isFinished = sfFalse;

	sfIntRect rect = sfSprite_getTextureRect(_anim->sprite);

	rect.left = (int)_anim->start.x + rect.width * (_anim->currentFrame - 1);

	sfSprite_setTextureRect(_anim->sprite, rect);
}

void CleanUpAnimation(Anim* _anim)
{
    sfTexture_destroy(_anim->texture);
    sfSprite_destroy(_anim->sprite);
	_anim->texture = NULL;
	_anim->sprite = NULL;
}
