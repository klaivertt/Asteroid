#include "Text.h"

TextManager text = { 0 };

void LoadTextManager(void)
{
	text.font = sfFont_createFromFile("Assets/Fonts/Asteroid 7337.ttf");
}
sfText* InitText(const char* _string, unsigned int _fontSize, sfVector2f _position)
{
	sfText* tempText = sfText_create();
	sfText_setFont(tempText, text.font);
	sfText_setCharacterSize(tempText, _fontSize);
	sfText_setPosition(tempText, _position);
	sfText_setString(tempText, _string);
	return tempText;
}

sfText* InitTextWithValue(const char* _string, int _value, unsigned int _fontSize, sfVector2f _position)
{
	sfText* tempText = sfText_create();
	sfText_setFont(tempText, text.font);
	sfText_setCharacterSize(tempText, _fontSize);
	sfText_setPosition(tempText, _position);
	sfText_setString(tempText, _string);

	char string[50];
	sprintf_s(string, sizeof(string), _string, _value);
	sfText_setString(tempText, string);

	return tempText;
}


void UpdateText(sfText** _text, const char* _string, int _value)
{
	char string[50];
	sprintf_s(string, sizeof(string), _string, _value);
	sfText_setString(*_text, string);
}
