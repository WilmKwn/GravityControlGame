#pragma once

#include "Graphics.h"
#include "Window.h"

class MenuScreen
{
public:
	MenuScreen(Graphics* graphics, HWND window_handle);
	~MenuScreen();

	void Init();

	void Run();

	void SetPlayButtonPressed(bool play);
	bool GetPlayButtonPressed();

private:
	Graphics* graphics;

	POINT cursorPos;

	RECT window;

	RECT playButton, instructions, optionsButton, creditsButton;

	bool playButtonPressed;
	bool optionsButtonPressed;
	bool creditsButtonPressed;
};