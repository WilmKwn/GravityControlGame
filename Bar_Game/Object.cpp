#include "Object.h"

Object::Object(Graphics* graphics)
{
	this->graphics = graphics;
	srand((unsigned)time(NULL));
}

Object::~Object()
{
}

void Object::ResetLeft()
{
	object = { gamefield.left, gamefield.top, gamefield.left + objectSize, gamefield.top + objectSize };
	fallSpeed = originalFallSpeed;
}

void Object::ResetRight()
{
	object = { gamefield.right - objectSize, gamefield.top, gamefield.right, gamefield.top + objectSize };
	fallSpeed = originalFallSpeed;
}

void Object::DeadObject()
{
	isDead = true;
	object = { -5000, -5000, -5000, -5000 };
}

void Object::ChangeColor(int color)
{
	this->color = color;

	if (color == 0) object_color = D2D1::ColorF(1.0f, 0.0f, 0.0f);
	else if (color == 1) object_color = D2D1::ColorF(0.0f, 1.0f, 0.0f);
	else if (color == 2) object_color = D2D1::ColorF(0.0f, 0.0f, 1.0f);
}

void Object::SetTopLeftPos(int left, int top, int right, int bottom)
{
	object.left = left;
	object.top = top;
	object.right = right;
	object.bottom = bottom;
}

void Object::SetStayOnBar(bool stay)
{
	stayOnBar = stay;
}

void Object::SetStayOnObject(bool stay)
{
	stayOnObject = stay;
}

void Object::SetIsDead(bool dead)
{
	isDead = dead;
}

void Object::SetIsStored(bool stored)
{
	isStored = stored;
}

void Object::SetStoreOnObject(bool store)
{
	storeOnObject = store;
}

void Object::SetStoreBottom(bool store)
{
	storeBottom = store;
}

void Object::SetMinus(bool minus)
{
	this->minus = minus;
}

void Object::SetStoreMinus(bool minus)
{
	storeMinus = minus;
}

bool Object::TouchedBottom()
{
	if (object.bottom >= gamefield.bottom) touchedBottom = true;
	return touchedBottom;
}

bool Object::GetStayOnBar()
{
	return stayOnBar;
}

bool Object::GetStayOnObject()
{
	return stayOnObject;
}

bool Object::GetIsDead()
{
	return isDead;
}

bool Object::GetIsStored()
{
	return isStored;
}

bool Object::GetMinus()
{
	return minus;
}

bool Object::GetStoreMinus()
{
	return storeMinus;
}

bool Object::GetStoreOnObject()
{
	return storeOnObject;
}

bool Object::GetStoreBottom()
{
	return storeBottom;
}

int Object::GetColor()
{
	return color;
}

RECT Object::GetRect()
{
	return object;
}

void Object::Fall()
{
	(!fallPos) ? object.left += arcSize : object.left -= arcSize;
	switch (fallPos)
	{
	case 0:
		object.top += fallSpeed;
		fallSpeed *= 1.05;
		object.bottom = object.top + 10;
		object.right = object.left + 10;
		break;
	case 1:
		object.top += fallSpeed;
		fallSpeed *= 1.05;
		object.bottom = object.top + 10;
		object.right = object.left + 10;
		break;
	}
}

void Object::Init(RECT gamefield, RECT window, float fallSpeed, int maxArcSize)
{
	this->gamefield = gamefield;
	this->window = window;

	objectSize = 10;
	object_color = D2D1::ColorF(1.0f, 0.0f, 0.0f);
	object = { gamefield.left, gamefield.top, gamefield.left + objectSize, gamefield.top + objectSize };

	this->fallSpeed = fallSpeed;
	originalFallSpeed = fallSpeed;

	this->maxArcSize = maxArcSize;

	stayOnBar = false;
	stayOnObject = false;
	touchedBottom = false;
	isDead = false;
	isStored = false;
	storeOnObject = false;
	storeBottom = false;
	minus = false;
	storeMinus = false;

	fallPos = rand() % 2;
	(!fallPos) ? ResetLeft() : ResetRight();

	// min + (rand() % (max - min + 1) )
	arcSize = 1 + (rand() % (maxArcSize - 1 + 1));
}

void Object::Run()
{
	graphics->DrawRect(object, object_color);
}