#pragma once

#include <iostream>
#include <time.h>

#include "Graphics.h"

class Object
{
public:
	Object(Graphics* graphics);
	~Object();

	void Init(RECT gamefield, RECT window, float fallSpeed, int maxArcSize);
	void Run();

	void Fall();

	void ResetLeft();
	void ResetRight();
	void DeadObject();

	void ChangeColor(int color);

	void SetTopLeftPos(int left, int top, int right, int bottom);
	void SetStayOnBar(bool stay);
	void SetStayOnObject(bool stay);
	void SetIsDead(bool dead);
	void SetIsStored(bool stored);
	void SetStoreOnObject(bool store);
	void SetStoreBottom(bool store);
	void SetMinus(bool minus);
	void SetStoreMinus(bool minus);

	bool TouchedBottom();
	bool GetStayOnBar();
	bool GetStayOnObject();
	bool GetStoreOnObject();
	bool GetStoreBottom();
	bool GetIsStored();
	bool GetIsDead();
	bool GetMinus();
	bool GetStoreMinus();
	int GetColor();
	RECT GetRect();

private:
	Graphics* graphics;

	RECT object, gamefield, window;

	int objectSize;

	int color;
	D2D1_COLOR_F object_color;

	float fallSpeed;
	float originalFallSpeed;
	float arcSize;
	int maxArcSize;

	bool fallPos;

	bool stayOnBar;
	bool stayOnObject;
	bool storeOnObject;
	bool storeBottom;
	bool touchedBottom;
	bool isStored;
	bool isDead;

	bool minus;
	bool storeMinus;
};