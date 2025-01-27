#include "Wraparound.h"

void DrawWraparound(sfRenderWindow* const _renderWindow, sfSprite* _sprite, sfVector2f _position)
{
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	// Draw at the middle of each edge
	sfSprite_setPosition(_sprite, (sfVector2f){ _position.x, _position.y + SCREEN_HEIGHT});
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x, _position.y - SCREEN_HEIGHT });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x + SCREEN_WIDTH, _position.y });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x - SCREEN_WIDTH, _position.y });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	// Draw at each corner
	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x + SCREEN_WIDTH, _position.y + SCREEN_HEIGHT });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x - SCREEN_WIDTH, _position.y + SCREEN_HEIGHT });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x + SCREEN_WIDTH, _position.y - SCREEN_HEIGHT });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, (sfVector2f) { _position.x - SCREEN_WIDTH, _position.y - SCREEN_HEIGHT });
	sfRenderWindow_drawSprite(_renderWindow, _sprite, NULL);

	sfSprite_setPosition(_sprite, _position);
}
