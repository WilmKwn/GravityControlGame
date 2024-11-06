#include "Gamefield.h"

Gamefield::Gamefield(Graphics* graphics)
{
	this->graphics = graphics;
}

Gamefield::~Gamefield()
{
}

RECT Gamefield::GetField()
{
	return field;
}

RECT Gamefield::GetBar()
{
	return bar;
}

Gamefield::BarColor Gamefield::GetBarColor()
{
	return barColor;
}

int Gamefield::GetStorageColor()
{
	return storageColor;
}

// DOESNT SEEM TO REPEAT DOEEE
void Gamefield::ShakeEffect(bool shake)
{
	/*int shakeSize = 4;
	if (shakeEffectCounter <= 20 && shakeEffectCounter >= 0) {
		shakeEffectCounter++;

		if (shakeEffectCounter % 3) {
			field.left += shakeSize;
			field.right += shakeSize;
		}
		else if ((shakeEffectCounter % 3) == 1) {
			field.left -= shakeSize;
			field.right -= shakeSize;
		}
		else {
			field = { (LONG)(window.right*0.25), window.top, (LONG)(window.right*0.75), (LONG)(window.bottom*0.75) };
		}
	}
	else {
		shakeEffectCounter = -1;
		field = { (LONG)(window.right*0.25), window.top, (LONG)(window.right*0.75), (LONG)(window.bottom*0.75) };
	}*/
	field.left += 5;
	field.right += 5;
}

void Gamefield::ScoreGoOff(bool scored, int x, int y)
{
	if (scored) {
		graphics->DrawTexts(L"+1", 25.0f, -1, x, y, D2D1::ColorF(0.0f, 1.0f, 0.0f));
	}
	else {
		graphics->DrawTexts(L"-1", 25.0f, -1, x, y, D2D1::ColorF(1.0f, 0.0f, 0.0f));
	}
}

void Gamefield::Init(RECT window)
{
	this->window = window;
	field = { (LONG)(window.right * 0.25), window.top, (LONG)(window.right * 0.75), (LONG)(window.bottom * 0.75) };
	bar = { (LONG)(window.right * 0.5) - 20, (LONG)(window.bottom * 0.5) - 5, (LONG)(window.right * 0.5) + 20, (LONG)(window.bottom * 0.5) + 5 };

	barColor = eNone;
	bar_color = D2D1::ColorF(1.0f, 1.0f, 1.0f);

	scoreNumber = 0;
	temp_number = std::to_wstring(scoreNumber);
	scoreText = temp_number.c_str();

	livesNumber = 3;
	temp_number = std::to_wstring(livesNumber);
	livesText = temp_number.c_str();
}

void Gamefield::Run(POINT cursor, int score, int lives, int level, bool allUsed)
{
	// FIELD
	graphics->DrawRect(field, D2D1::ColorF(1.0f, 1.0f, 1.0f));

	// LEVEL INDICATION
	levelNumber = level;
	temp_number = std::to_wstring(levelNumber);
	levelText = temp_number.c_str();
	graphics->DrawTexts(L"LEVEL:", 30.0f, 2, window.left + 10, field.top + 10, D2D1::ColorF(1.0f, 1.0f, 1.0f));
	graphics->DrawTexts(levelText, 30.0f, -2, window.left + 120, field.top + 10, D2D1::ColorF(1.0f, 0.0f, 0.0f));
	RECT rect = { window.left, field.top + 10, window.left + 140, field.top + 50 };
	graphics->DrawRect(rect, D2D1::ColorF(0.5f, 0.5f, 0.5f));

	// SCORE
	scoreNumber = score;
	temp_number = std::to_wstring(scoreNumber);
	scoreText = temp_number.c_str();

	graphics->DrawTexts(L"SCORE:", 20.0f, 2, window.right / 2 + 30, field.top + 10, D2D1::ColorF(0.0f, 1.0f, 1.0f));
	graphics->DrawTexts(scoreText, 20.0f, -2, window.right / 2 + 110, field.top + 10, D2D1::ColorF(1.0f, 1.0f, 1.0f));

	// LIVES
	graphics->DrawTexts(L"LIFE:", 20.0f, 1, field.left + 60, field.top + 10, D2D1::ColorF(1.0f, 1.0f, 0.0f));
	if (lives == 3) graphics->DrawTexts(L"❤❤❤", 20.0f, +1, field.left + 110, field.top + 10, D2D1::ColorF(1.0f, 0.0f, 0.0f));
	if (lives == 2) graphics->DrawTexts(L"❤❤", 20.0f, 0, field.left + 110, field.top + 10, D2D1::ColorF(1.0f, 0.0f, 0.0f));
	if (lives == 1) graphics->DrawTexts(L"❤", 20.0f, -2, field.left + 110, field.top + 10, D2D1::ColorF(1.0f, 0.0f, 0.0f));

	// BAR
	bar.left = cursor.x - 20;
	bar.right = cursor.x + 20;
	if (cursor.x - 20 < field.left) {
		bar.left = field.left + 2;
		bar.right = bar.left + 40;
	}
	else if (cursor.x + 20 > field.right) {
		bar.right = field.right - 2;
		bar.left = bar.right - 40;
	}
	if (!allUsed) {
		if (KEY_DOWN(VK_A)) {
			barColor = eRed;
			bar_color = D2D1::ColorF(1.0f, 0.0f, 0.0f);
		}
		else if (KEY_DOWN(VK_S)) {
			barColor = eGreen;
			bar_color = D2D1::ColorF(0.0f, 1.0f, 0.0f);
		}
		else if (KEY_DOWN(VK_D)) {
			barColor = eBlue;
			bar_color = D2D1::ColorF(0.0f, 0.0f, 1.0f);
		}
	}
	else {
		bar_color = D2D1::ColorF(1.0f, 1.0f, 1.0f);
	}
	graphics->DrawRect(bar, bar_color);

	// STORAGE
	int third_of_field = (int)((field.right - field.left) / 3);
	for (int i = 1; i < 4; i++) {
		D2D1_COLOR_F color;
		int colors[3] = { 0, 1, 2 };
		int storage_color = colors[i - 1];
		switch (storage_color) {
		case 0:
			color = D2D1::ColorF(1.0f, 0.0f, 0.0f); break;
		case 1:
			color = D2D1::ColorF(0.0f, 1.0f, 0.0f); break;
		case 2:
			color = D2D1::ColorF(0.0f, 0.0f, 1.0f); break;
		default: break;
		}
		graphics->DrawLine(D2D1::Point2F(field.left + (third_of_field) * (i - 1), field.bottom), D2D1::Point2F(field.left + (third_of_field)*i, field.bottom), color);
		graphics->DrawLine(D2D1::Point2F(field.left + (third_of_field) * (i - 1), window.bottom - 1), D2D1::Point2F(field.left + (third_of_field)*i, window.bottom - 1), color);
	}
	for (int i = 0; i < 4; i++) {
		graphics->DrawLine(D2D1::Point2F(field.left + (third_of_field)*i, field.bottom), D2D1::Point2F(field.left + (third_of_field)*i, window.bottom), D2D1::ColorF(1.0f, 1.0f, 1.0f));
	}

	int CenterBar = bar.left + ((bar.right - bar.left) / 2);
	if (CenterBar >= field.left && CenterBar <= field.left + third_of_field) storageColor = 0;
	else if (CenterBar >= field.left + third_of_field && CenterBar <= field.left + third_of_field * 2) storageColor = 1;
	else if (CenterBar >= field.left + third_of_field * 2 && CenterBar <= field.right) storageColor = 2;
}