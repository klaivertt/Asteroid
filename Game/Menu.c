#include "Menu.h"
#include "Collision.h"
#include "GameState.h"

Menu menu = { 0 };

void LoadMenuBackground(void);
void DrawMenuBackground(sfRenderWindow*);

void LoadMenuPlayer(void);
void UpdateMenuPlayer(float);
void DrawMenuPlayer(sfRenderWindow*);

void LoadMenuButton(void);
void ButtonChangeState(sfRenderWindow* const _render);
void UpdateMenuButton(float);
void DrawMenuButton(sfRenderWindow*);

#pragma region GameLoop

void LoadMenu(void)
{
	LoadMenuBackground();
	LoadMenuPlayer();
	LoadMenuButton();
}


void OnKeyPressedMenu(sfKeyEvent _key, sfRenderWindow* const _render)
{
	switch (_key.code)
	{
	case sfKeyZ:
		menu.currentButton--;
		if (menu.currentButton < 0)
		{
			menu.currentButton = MAX_BUTTONS - 1;
		}
		break;
	case sfKeyS:
		menu.currentButton++;
		if (menu.currentButton > MAX_BUTTONS - 1)
		{
			menu.currentButton = 0;
		}
		break;
	case sfKeyUp:
		menu.currentButton--;
		if (menu.currentButton < 0)
		{
			menu.currentButton = MAX_BUTTONS - 1;
		}
		break;
	case sfKeyDown:
		menu.currentButton++;
		if (menu.currentButton > MAX_BUTTONS - 1)
		{
			menu.currentButton = 0;
		}
		break;
	case sfKeySpace:
		ButtonChangeState(_render);
		break;
	case sfKeyEnter:
		ButtonChangeState(_render);
		break;
	default:
		break;
	}
}

void UpdateMenu(float _dt)
{
	UpdateMenuPlayer(_dt);
	UpdateMenuButton(_dt);
}

void DrawMenu(sfRenderWindow* _render)
{
	DrawMenuBackground(_render);
	DrawMenuPlayer(_render);
	DrawMenuButton(_render);
}

void CleanMenu(void)
{
}

#pragma endregion

#pragma region Background
void LoadMenuBackground(void)
{
	menu.background.texture = sfTexture_createFromFile("Assets/Interfaces/Menu/Backgrounds/01.png", NULL);
	menu.background.sprite = sfSprite_create();

	sfSprite_setTexture(menu.background.sprite, menu.background.texture, sfTrue);
}

void DrawMenuBackground(sfRenderWindow* _render)
{
	sfRenderWindow_drawSprite(_render, menu.background.sprite, NULL);
}

#pragma endregion

#pragma region Player

void LoadMenuPlayer(void)
{
	CreateAnimation(&menu.playerIdle, "Assets/Sprites/Player/CharacterIdle.png", 6, 6, 6, sfTrue, (sfVector2f) { 0, 0 });

	menu.currentAnim = &menu.playerIdle;

	sfSprite_setPosition(menu.currentAnim->sprite, (sfVector2f) { SCREEN_W * 0.7, SCREEN_H * 0.585 });
}

void UpdateMenuPlayer(float _dt)
{
	UpdateAnimation(menu.currentAnim, _dt);
}

void DrawMenuPlayer(sfRenderWindow* _render)
{
	//sfRenderWindow_drawSprite(_render, menu.currentAnim->sprite, NULL);
}

void CleanupMenu()
{

}
#pragma endregion

#pragma region Buttons

void LoadMenuButton(void)
{
	sfTexture* textures[MAX_BUTTONS];
	textures[0] = sfTexture_createFromFile("Assets/Interfaces/Menu/Play.png", NULL);
	textures[1] = sfTexture_createFromFile("Assets/Interfaces/Menu/Custom.png", NULL);
	textures[2] = sfTexture_createFromFile("Assets/Interfaces/Menu/Settings.png", NULL);
	textures[3] = sfTexture_createFromFile("Assets/Interfaces/Menu/Credits.png", NULL);
	textures[4] = sfTexture_createFromFile("Assets/Interfaces/Menu/Exit.png", NULL);

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		Button* button = &menu.buttons[i];

		button->image.texture = textures[i];
		button->image.sprite = sfSprite_create();

		sfSprite_setTexture(button->image.sprite, button->image.texture, sfTrue);
		float y = (SCREEN_H * 0.5) - (100 * 1) + 100 * (i - 1);
		sfSprite_setPosition(button->image.sprite, (sfVector2f) { 50, y });
		sfFloatRect rect = sfSprite_getLocalBounds(button->image.sprite);

		button->rectangle = sfRectangleShape_create();
		sfRectangleShape_setSize(button->rectangle, (sfVector2f) { rect.width, rect.height });
		sfRectangleShape_setPosition(button->rectangle, (sfVector2f) { 50, y });
		sfRectangleShape_setOutlineThickness(button->rectangle, 3.0f);
		sfRectangleShape_setFillColor(button->rectangle, sfColor_fromRGBA(0, 0, 0, 0));
	}

	menu.currentButton = 0;
}

void ButtonChangeState(sfRenderWindow* const _render)
{
	switch (menu.currentButton)
	{
	case 0:
		SetGameState(GAME);
		break;
	case 2:
		//SetGameState(GAME);
		break;
	case 4:
		sfRenderWindow_close(_render);
		break;
	default:
		break;
	}
}

void UpdateMenuButton(float _dt)
{
}

void DrawMenuButton(sfRenderWindow* _render)
{
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		sfRenderWindow_drawSprite(_render, menu.buttons[i].image.sprite, NULL);
	}

	sfRenderWindow_drawRectangleShape(_render, menu.buttons[menu.currentButton].rectangle, NULL);

}

#pragma endregion