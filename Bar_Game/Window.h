#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	void Init(HINSTANCE hInstance, int x, int y, int width, int height);

	HWND GetHandle();

	static bool GetLBClick() { return LB_click; }

	static void SetLBClickValue(bool value) { LB_click = value; }

private:
	HWND m_handle;

	static bool LB_click;
};