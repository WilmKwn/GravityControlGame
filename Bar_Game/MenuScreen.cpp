#include "MenuScreen.h"

MenuScreen::MenuScreen(Graphics* graphics, HWND window_handle)
{
	this->graphics = graphics;

	GetClientRect(window_handle, &window);
}

MenuScreen::~MenuScreen()
{
}

bool MenuScreen::GetPlayButtonPressed()
{
	return playButtonPressed;
}

void MenuScreen::SetPlayButtonPressed(bool play)
{
	playButtonPressed = play;
}

void MenuScreen::Init()
{
	playButtonPressed = false;
	optionsButtonPressed = false;
	creditsButtonPressed = false;

	playButton = { (window.right / 2) - 50, (window.bottom / 2), (window.right / 2) + 50, (window.bottom / 2) + 40 };
}

void MenuScreen::Run()
{
	GetCursorPos(&cursorPos);

	// THE PLAY BUTTON
	if (cursorPos.x > playButton.left && cursorPos.x < playButton.right && cursorPos.y > playButton.top && cursorPos.y < playButton.bottom) {
		graphics->DrawRect(playButton, D2D1::ColorF(1.0f, 1.0f, 0.0f));
		graphics->DrawTexts(L"PLAY", 40.0f, 1, playButton.left, playButton.top, D2D1::ColorF(1.0f, 1.0f, 1.0f));
	}
	else {
		graphics->DrawTexts(L"PLAY", 40.0f, 1, playButton.left, playButton.top, D2D1::ColorF(1.0f, 1.0f, 1.0f));
	}

	if (cursorPos.x > playButton.left && cursorPos.x < playButton.right && cursorPos.y > playButton.top && cursorPos.y < playButton.bottom && Window::GetLBClick()) {
		playButtonPressed = true;
	}
}