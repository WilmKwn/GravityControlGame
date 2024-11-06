#pragma once

#include "Graphics.h"
#include "Window.h"

#include <string>
#include <sstream>

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0

#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

class Gamefield
{
public:
	Gamefield(Graphics* graphics);
	~Gamefield();

	void Init(RECT window);
	void Run(POINT cursor, int score, int lives, int level, bool allUsed);

	void ShakeEffect(bool shake);

	void ScoreGoOff(bool scored, int x, int y);

	RECT GetField();
	RECT GetBar();

	enum BarColor {
		eRed, eGreen, eBlue, eNone
	};

	BarColor GetBarColor();
	int GetStorageColor();

private:
	Graphics* graphics;

	RECT window;
	RECT field, bar;

	BarColor barColor;
	D2D1_COLOR_F bar_color;

	int storageColor;

	int scoreNumber;
	std::wstring temp_number;
	const wchar_t* scoreText;

	int livesNumber;
	const wchar_t* livesText;

	int levelNumber;
	const wchar_t* levelText;
};