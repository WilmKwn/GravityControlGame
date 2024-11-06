#pragma once

#include <iostream>
#include <time.h>

#include "Window.h"

#include "Gamefield.h"
#include "Object.h"

class Game
{
public:
	Game(Graphics* graphics, HWND window_handle);
	~Game();

	void Init(float speed, int maxArcSize, int level);
	void Run(int tScore, int life);

	bool RectCollide(RECT rect1, RECT rect2);

	void RunObject(int index, bool isFirst);

	void GameOver();
	void CountDown();

	bool GetReturnMenuScreen();
	bool GetLevelOver();
	int GetTotalScore();
	int GetLives();

	void SetAddScore(bool add);
	bool GetAddScore();

private:
	Graphics* graphics;

	Gamefield* gamefield;

	Object* object[5];
	int objectArraySize;

	RECT window;

	POINT cursor;

	bool anotherObjectStored;
	bool pressed;
	bool allObjectUsed;

	bool minusScore;

	bool countDown;
	int countDownCounter;

	bool scoreGoOff;
	bool scoreGoOffMinus;
	int scoreCounter;
	int goOffX;

	int storedObjectIndex;

	int storageScore[3];
	int possibleScore;
	int totalScore;
	int totalTotalScore;
	int lives;

	bool minusLives;

	bool levelOver;
	bool gameOver;

	bool addScore;
	bool continueLives;

	bool returnMenuScreen;
	bool retry;
	bool quit;

	int level;
};