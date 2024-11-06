#pragma once

#include <d2d1.h>
#include <dwrite.h>

class Graphics
{
public:
	Graphics();
	~Graphics();

	void Init(HWND windowHandle);

	void Begin();
	void End();

	void ClearScreen(D2D1_COLOR_F color);

	void DrawRect(RECT rect, D2D1_COLOR_F color);
	void DrawLine(D2D1_POINT_2F  p1, D2D1_POINT_2F  p2, D2D1_COLOR_F color);

	void DrawTexts(const WCHAR* text, float size, int length, int x, int y, D2D1_COLOR_F color);

private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

	ID2D1SolidColorBrush* brush;

	IDWriteFactory* writeFactory;
	IDWriteTextFormat* textFormat;
};