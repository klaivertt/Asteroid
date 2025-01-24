#include "Common.h"
#include "GameState.h"
#include "Menu.h"
#include "Game.h"
#include "GameOver.h"
#include "Text.h"

#pragma region Struct
typedef struct MainData
{
	sfRenderWindow* renderWindow;
	sfClock* clock;
}MainData;

#pragma endregion

#pragma region GameLoop
void Load(MainData* const _mainData);
void PollEvent(sfRenderWindow* const _renderWindow);
void KeyPressed(sfRenderWindow* const _renderWindow, sfKeyEvent _key);
void Update(MainData* const _mainData);
void Draw(sfRenderWindow* const _renderWindow);
void Cleanup(MainData* const _mainData);
#pragma endregion

#pragma region Functions
void LoadMainData(MainData* const _mainData);
void CleanupMainData(MainData* const _mainData);
#pragma endregion

int main(void)
{
	MainData mainData = { 0 };

	Load(&mainData);
	while (sfRenderWindow_isOpen(mainData.renderWindow))
	{
		PollEvent(mainData.renderWindow);
		Update(&mainData);
		Draw(mainData.renderWindow);
	}
	Cleanup(&mainData);

	return EXIT_SUCCESS;
}

void Load(MainData* const _mainData)
{
	srand(_getpid());
	LoadTextManager();
	LoadMainData(_mainData);
	SetGameState(MENU);
}

void PollEvent(sfRenderWindow* const _renderWindow)
{
	sfEvent event;
	while (sfRenderWindow_pollEvent(_renderWindow, &event))
	{
		switch (event.type)
		{
		case sfEvtClosed:
			sfRenderWindow_close(_renderWindow);
			break;
		case sfEvtKeyPressed:
			KeyPressed(_renderWindow, event.key);
			break;
		default:
			break;
		}
	}
}

void KeyPressed(sfRenderWindow* const _renderWindow, sfKeyEvent _key)
{
	switch (GetGameState())
	{
	case MENU:
		KeyPressedMenu(_renderWindow, _key);
		break;
	case GAME:
		KeyPressedGame(_key);
		break;
	case GAME_OVER:
		KeyPressedGameOver(_key);
		break;
	default:
		break;
	}
}

void Update(MainData* const _mainData)
{
	float dt = sfTime_asSeconds(sfClock_restart(_mainData->clock));

	switch (GetGameState())
	{
	case MENU:
		UpdateMenu(_mainData->renderWindow, dt);
		break;
	case GAME:
		UpdateGame(_mainData->renderWindow, dt);
		break;
	case GAME_OVER:
		UpdateGameOver(_mainData->renderWindow, dt);
		break;
	default:
		break;
	}
}

void Draw(sfRenderWindow* const _renderWindow)
{
	sfRenderWindow_clear(_renderWindow, sfBlack);

	switch (GetGameState())
	{
	case MENU:
		DrawMenu(_renderWindow);
		break;
	case GAME:
		DrawGame(_renderWindow);
		break;
	case GAME_OVER:
		DrawGameOver(_renderWindow);
		break;
	default:
		break;
	}

	sfRenderWindow_display(_renderWindow);
}

void Cleanup(MainData* const _mainData)
{
	CleanupMainData(_mainData);

	switch (GetGameState())
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
	default:
		break;
	}
}

void LoadMainData(MainData* const _mainData)
{
	_mainData->clock = sfClock_create();
	sfVideoMode videoMode = { SCREEN_WIDTH, SCREEN_HEIGHT, BPP };
	_mainData->renderWindow = sfRenderWindow_create(videoMode, GAME_NAME, sfDefaultStyle, NULL);
	sfRenderWindow_setFramerateLimit(_mainData->renderWindow, 60);
	sfRenderWindow_setKeyRepeatEnabled(_mainData->renderWindow, sfFalse);
}

void CleanupMainData(MainData* const _mainData)
{
	sfClock_destroy(_mainData->clock);
	_mainData->clock = NULL;
	sfRenderWindow_destroy(_mainData->renderWindow);
	_mainData->renderWindow = NULL;
}
