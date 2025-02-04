#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "Common.h"

//Structure for managing CSFML text
typedef struct {
	sfFont* font;
} TextManager;

// *@brief Function to load and initialize the text manager resources
void LoadTextManager(void);

// *@brief Function to initialize a text object with specific attributes
// *
// *@param _text: Pointer to the sfText object to initialize
// *@param _string: The string to be displayed by the text
// *@param _fontSize: The font size for the text
// *@param _position: The position of the text on the screen
sfText* InitText(const char* _string, unsigned int _fontSize, sfVector2f _position);

// *@brief Function to initialize a text object with specific attributes
// *
// *@param _text: Pointer to the sfText object to initialize
// *@param _string: The string to be displayed by the text
// *@param _value: The value to be displayed by the text
// *@param _fontSize: The font size for the text
// *@param _position: The position of the text on the screen
sfText* InitTextWithValue(const char* _string, int _value, unsigned int _fontSize, sfVector2f _position);

// *@brief Function to update the content of a text object with a new string and value
// *
// *@param _text: Pointer to the sfText object to update
// *@param _string: The base string to be updated
// *@param _value: An integer value to append to the string
void UpdateText(sfText** _text, const char* _string, int _value);

// *@brief Function to clean the text object
// *
// *@param _text: Pointer to the sfText object to clean
void CleanupText(sfText** _text);

// *@brief Function to resize the text object
// *
// *@param _text: Pointer to the sfText object to resize
void ResizeText(sfText* _text, unsigned int _fontSize);

// *@brief Function to set the origin of the text object
// *
// *@param _text: Pointer to the sfText object to set the origin
// *@param _origin: The origin of the text object
void SetTextOrigin(sfText* _text, sfVector2f _origin);

// *@brief Function to draw the text object on the screen
// *
// *@param _renderWindow: Pointer to the sfRenderWindow object to draw the text on
// *@param _text: Pointer to the sfText object to draw
void DrawText(sfRenderWindow* const _renderWindow, sfText* _text);
#endif
